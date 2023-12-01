#include "../../include/Peers/requester.h"

using namespace std;

Requester::Requester(unsigned short port) : Peer() {
    setupServer("127.0.0.1", to_string(port).c_str());
}

Requester::~Requester() noexcept {}

void Requester::set_task_request(TaskRequest request_) {
    // push large task request into the vector
    taskRequests.push_back(request_);
}

void Requester::send_discovery_request() {
    // update the member hash map
    leaderIP = IpAddress{bootstrapNode.getLeaderIpAddress(),
                         bootstrapNode.getLeaderPort()};

    taskRequests[0].setLeaderUuid(bootstrapNode.getLeaderUuid());
    
    // add the follower peers
    // providerPeers.insert({"1", IpAddress{"8.tcp.ngrok.io", 13299}});
}

void Requester::divide_task() {
    // divide the large task into subtasks
    // divide "[2, 1, 4, 3, 6, 5, 9, 7, 8, 10]" into as many subtasks as
    // there

    // parse string array as vector
    vector<int> trainingData = taskRequests[0].getTrainingData();

    // divide the vector into subvectors
    int numSubtasks = providerPeers.size() + 1;
    int subtaskSize = trainingData.size() / numSubtasks;
    int remainder = trainingData.size() % numSubtasks;

    // create subvectors of requesttasks
    vector<TaskRequest> subtasks;
    for (int i = 0; i < numSubtasks; i++) {
        vector<int> subtaskData;
        for (int j = 0; j < subtaskSize; j++) {
            subtaskData.push_back(trainingData[i * subtaskSize + j]);
        }

        TaskRequest subtaskRequest = TaskRequest(subtaskData);
        subtaskRequest.setLeaderUuid(taskRequests[0].getLeaderUuid());
        subtaskRequest.setAssignedPeers(taskRequests[0].getAssignedPeers());
        taskRequests.push_back(subtaskRequest);
    }

    // add the remainder to the last subtask
    if (remainder != 0) {
        vector<int> subtaskData;
        for (int i = 0; i < remainder; i++) {
            subtaskData.push_back(trainingData[numSubtasks * subtaskSize + i]);
        }

        TaskRequest subtaskRequest = TaskRequest(subtaskData);
        subtaskRequest.setLeaderUuid(taskRequests[0].getLeaderUuid());
        subtaskRequest.setAssignedPeers(taskRequests[0].getAssignedPeers());
        taskRequests.push_back(subtaskRequest);
    }

    // remove the large task request
    taskRequests.erase(taskRequests.begin());
}

void Requester::send_task_request() {
    // divides the task into subtasks
    divide_task();

    // send the task request to the leader peer
    // serialize the requests
    string serializedRequest = taskRequests[0].serialize();
    const char* host = leaderIP.ipAddress.c_str();
    const char* port = std::to_string(leaderIP.port).c_str();
    client->setUpConn(host, port, "tcp");
    client->sendRequest(serializedRequest.c_str());

    // send the task request to the provider peers
    int ctr = 1;
    for (auto peer : providerPeers) {
        // serialize the requests
        string serializedRequest = taskRequests[ctr].serialize();

        // set up the client
        const char* host = peer.second.ipAddress.c_str();
        const char* port = std::to_string(peer.second.port).c_str();
        client->setUpConn(host, port, "tcp");

        // send the request
        client->sendRequest(serializedRequest.c_str());
        ctr++;
    }
}

void Requester::check_status() {}

TaskResponse Requester::get_results() { return TaskResponse(); }
