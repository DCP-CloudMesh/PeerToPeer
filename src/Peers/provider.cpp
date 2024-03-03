#include "../../include/Peers/provider.h"
#include "../../include/Peers/bootstrap_node.h"
#include "../../include/RequestResponse/message.h"
#include "../../include/RequestResponse/generic_response.h"
#include "../../include/RequestResponse/registration.h"
#include "../../include/RequestResponse/task_request.h"
#include "../../include/utility.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <algorithm>

using namespace std;

Provider::Provider(const char* port, string uuid) : Peer(uuid) {
    isBusy = false;
    isLocalBootstrap = false;

    setupServer("127.0.0.1", port);
}
Provider::~Provider() noexcept {}

void Provider::registerWithBootstrap() {
    const char* bootstrapHost = BootstrapNode::getServerIpAddress();
    const char* bootstrapPort = BootstrapNode::getServerPort();
    cout << "Connecting to bootstrap node at "
         << bootstrapHost << ":" << bootstrapPort << endl;
    client->setupConn(bootstrapHost, bootstrapPort, "tcp");

    shared_ptr<Registration> payload = make_shared<Registration>();
    Message msg(uuid, IpAddress(host, port), payload);

    client->sendMsg(msg.serialize().c_str());
}

void Provider::listen() {
    while (true) {
        cout << "Waiting for requester to connect..." << endl;
        if (!server->acceptConn()) continue;

        // receive task request object from client
        string requesterData = server->receiveFromConn();
        Message requesterMsg;
        requesterMsg.deserialize(requesterData);
        string requesterUuid = requesterMsg.getSenderUuid();
        IpAddress requesterIpAddr = requesterMsg.getSenderIpAddr();
        shared_ptr<Payload> requesterPayload = requesterMsg.getPayload();

        if (requesterPayload->getType() != Payload::Type::TASK_REQUEST) {
            continue;
        }

        server->replyToConn("Provider (" + uuid + ") - "
                            "Received task request.");
        shared_ptr<TaskRequest> taskReq =
            static_pointer_cast<TaskRequest>(requesterPayload);
        task = make_unique<TaskRequest>(std::move(*taskReq));
        server->replyToConn("Provider ID: " + uuid + " : Deserialized "
                            "task request. Now processing workload.\n");
        server->closeConn();

        if (task->getLeaderUuid() == uuid) {
            leaderHandleTaskRequest(requesterIpAddr);
        } else {
            followerHandleTaskRequest();
        }
    }
}

void Provider::leaderHandleTaskRequest(const IpAddress& requesterIpAddr) {
    // Run processWorkload() in a separate thread
    thread workloadThread(&Provider::processWorkload, this);

    vector<vector<int>> followerData{};
    while (followerData.size() < task->getAssignedWorkers().size() - 1) {
        cout << "\nWaiting for follower peer to connect..." << endl;
        while (!server->acceptConn());

        // get data from followers and aggregate
        string followerMsgStr = server->receiveFromConn();
        Message followerMsg;
        followerMsg.deserialize(followerMsgStr);
        shared_ptr<Payload> followerPayload = followerMsg.getPayload();

        if (followerPayload->getType() != Payload::Type::TASK_RESPONSE) {
            continue;
        }

        shared_ptr<TaskResponse> taskResp =
            static_pointer_cast<TaskResponse>(followerPayload);

        // append to followerData
        followerData.push_back(taskResp->getTrainingData());
        server->replyToConn("Received follower result.");
        server->closeConn();
    }

    cout << endl;
    workloadThread.join();
    TaskResponse aggregatedResults = aggregateResults(followerData);

    // Send results back to requester
    // TODO: requester IP address could change
    shared_ptr<TaskResponse> aggregatePayload =
        make_shared<TaskResponse>(aggregatedResults);
    Message aggregateResultMsg(uuid, IpAddress(host, port),
                                aggregatePayload);

    cout << "Waiting for connection back to requester" << endl;
    // Keep trying to send results back to requester 
    while (true) {
        // busy wait until connection is established
        while (client->setupConn(requesterIpAddr, "tcp") != 0) {
            sleep(5);
        }
        if (client->sendMsg(aggregateResultMsg.serialize().c_str()) != 0) {
            continue;
        }

        if (!server->acceptConn()) continue;

        // receive response from requester
        string serializedData = server->receiveFromConn();
        server->closeConn();
        // process this request
        Message msg;
        msg.deserialize(serializedData);
        shared_ptr<Payload> payload = msg.getPayload();

        if (payload->getType() == Payload::Type::GENERIC_RESPONSE) {
            shared_ptr<GenericResponse> gr =
                static_pointer_cast<GenericResponse>(payload);
            if (gr->getStatus() == GenericResponse::Status::SUCCESS) {
                break;
            }
        }
    }
}

void Provider::followerHandleTaskRequest() {
    processWorkload();
    cout << "Waiting for connection back to leader" << endl;
    IpAddress leaderIp =
        task->getAssignedWorkers()[task->getLeaderUuid()];
    // busy wait until connection is established with the leader
    while (client->setupConn(leaderIp, "tcp") == -1) {
        sleep(5);
    }
    client->sendMsg(task->serialize().c_str());
}

void Provider::processWorkload() {
    // data is stored in task->training data
    vector<int> data = task->getTrainingData();
    sort(data.begin(), data.end());
    // store result in task->trainingdata
    task->setTrainingData(data);
    cout << "Completed assigned workload" << endl;
}

TaskResponse Provider::aggregateResults(vector<vector<int>> followerData) {
    // get data from followers and aggregate
    vector<int> data = task->getTrainingData();
    for (auto follower : followerData) {
        data.insert(data.end(), follower.begin(), follower.end());
    }
    sort(data.begin(), data.end());
    TaskResponse taskResponse(data);
    return taskResponse;
}
