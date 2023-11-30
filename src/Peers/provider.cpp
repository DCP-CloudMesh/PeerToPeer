#include "../../include/Peers/provider.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <thread>

using namespace std;

Provider::Provider(unsigned short port) : Peer() {
    isBusy = false;
    isLocalBootstrap = false;

    setupServer("", to_string(port).c_str());
}

void Provider::listen() {
    while (true) {
        bool connStatus = server->acceptConn();
        if (connStatus) {
            // receive task request object from client
            string msg = server->receiveFromConn();
            server->replyToConn("Received task request.");

            // process this workload, first deserialize into a task
            task->deserialize(msg);
            server->replyToConn(
                "Deserialized task request. Now processing workload");
            server->closeConn();

            // Run processWorkload() in a separate thread
            thread workloadThread(&Provider::processWorkload, this);

            if (task->getLeaderUuid() == uuid) {
                // if this is the leader, send the result to the requester
                // send back the result
                vector<vector<int>> followerData;
                while (followerData.size() < task->getAssignedPeers().size()) {
                    bool connStatus = server->acceptConn();
                    // get data from followers and aggregate
                    string msg = server->receiveFromConn();
                    server->replyToConn("Received follower result.");
                    server->closeConn();
                    // deserialize into data
                    TaskResponse followerResult;
                    followerResult.deserialize(msg);
                    // append to followerData
                    followerData.push_back(followerResult.getTrainingData());
                }

                workloadThread.join();
                followerData.push_back(task->getTrainingData());

                TaskRequest aggregatedResults = aggregateResults(followerData);
                aggregatedResults.setLeaderUuid(task->getLeaderUuid());
                aggregatedResults.setAssignedPeers(task->getAssignedPeers());

                // send back the result to the requester
                // get the ip from the bootstrap server
                // ------------------ hard code for now ------------------
                const char* host = "8.tcp.ngrok.io";
                const char* port = "13299";
                client->setUpConn(host, port, "tcp");
                client->sendRequest(aggregatedResults.serialize().c_str());
            } else {
                // if this is a follower, send the result to the leader
                // send back the result

                // get the ip from the bootstrap server
                // ------------------ hard code for now ------------------
                const char* host = "8.tcp.ngrok.io";
                const char* port = "13299";
                client->setUpConn(host, port, "tcp");

                client->sendRequest(task->serialize().c_str());
            }
        }
    }
}

void Provider::processWorkload() {
    // data is stored in task->training data
    // assume data is vector<int> for now

    vector<int> data = task->getTrainingData();
    sort(data.begin(), data.end());
    cout << "Provider: data sorted." << endl;
    // store result in task->trainingdata
    task->setTrainingData(data);
}

TaskRequest Provider::aggregateResults(vector<vector<int>> followerData) {
    // get data from followers and aggregate
    vector<int> data = task->getTrainingData();
    for (auto follower : followerData) {
        data.insert(data.end(), follower.begin(), follower.end());
    }
    sort(data.begin(), data.end());
    task->setTrainingData(data);
    return *task;
}
