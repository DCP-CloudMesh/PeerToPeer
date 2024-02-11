#include "../../include/Peers/provider.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <algorithm>

using namespace std;

Provider::Provider(unsigned short port, string uuid) : Peer(uuid) {
    isBusy = false;
    isLocalBootstrap = false;

    setupServer("127.0.0.1", to_string(port).c_str());
}

void Provider::listen() {
    while (true) {
        cout << "Waiting for requester to connect..." << endl;
        bool connStatus = server->acceptConn();
        if (connStatus) {
            // receive task request object from client
            string msg = server->receiveFromConn();
            server->replyToConn("Provider ID: " + uuid +
                                " : Received task request.");
            // process this workload, first deserialize into a task
            task = make_unique<TaskRequest>(vector<int>());
            task->deserialize(msg);
            server->replyToConn(
                "Provider ID: " + uuid +
                " : Deserialized task request. Now processing workload.\n");
            server->closeConn();

            // Run processWorkload() in a separate thread
            thread workloadThread(&Provider::processWorkload, this);
            if (task->getLeaderUuid() == uuid) {
                // if this is the leader, send the result to the requester
                // send back the result
                vector<vector<int>> followerData{};
                while (followerData.size() <
                       task->getAssignedFollowers().size()) {
                    cout << endl;
                    cout << "Waiting for follower peer to connect..." << endl;
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

                cout << endl;

                workloadThread.join();

                TaskRequest aggregatedResults = aggregateResults(followerData);
                aggregatedResults.setLeaderUuid(task->getLeaderUuid());
                aggregatedResults.setAssignedFollowers(
                    task->getAssignedFollowers());

                // send back the result to the requester
                // get the ip from the bootstrap server
                // ------------------ hard code for now ------------------
                const char* host = bootstrapNode.getServerIpAddress().c_str();
                const char* port =
                    to_string(bootstrapNode.getServerPort()).c_str();
                cout << "Waiting for connection back to requester" << endl;

                // busy wait until connection is established
                while (client->setupConn(host, port, "tcp") == -1) {
                    sleep(5);
                }

                client->sendRequest(aggregatedResults.serialize().c_str());
            } else {
                // if this is a follower, send the result to the leader peer
                cout << "Waiting for connection back to leader" << endl;
                // get the ip from the bootstrap server
                // ------------------ hard code for now ------------------
                const char* leaderHost =
                    bootstrapNode.getLeaderIpAddress().c_str();
                const char* leaderPort =
                    to_string(bootstrapNode.getLeaderPort()).c_str();
                // busy wait until connection is established with the leader
                while (client->setupConn(leaderHost, leaderPort, "tcp") == -1) {
                    sleep(5);
                }
                workloadThread.join();
                client->sendRequest(task->serialize().c_str());
            }
        }
    }
}

void Provider::processWorkload() {
    // data is stored in task->training data
    vector<int> data = task->getTrainingData();
    sort(data.begin(), data.end());
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
