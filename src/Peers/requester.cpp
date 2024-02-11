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
    providerPeers.insert({bootstrapNode.getLeaderUuid(), leaderIP});

    // add the follower peers
    unordered_map<string, IpAddress> followerPeers{};
    IpAddress followerIP = IpAddress{bootstrapNode.getFollowerIpAddress(),
                                     bootstrapNode.getFollowerPort()};
    providerPeers.insert({bootstrapNode.getFollowerUuid(), followerIP});
    followerPeers.insert({bootstrapNode.getFollowerUuid(), followerIP});

    taskRequests[0].setAssignedFollowers(followerPeers);
}

void Requester::divide_task() {
    // divide the large task into subtasks
    // divide "[2, 1, 4, 3, 6, 5, 9, 7, 8, 10]" into as many subtasks as
    // there

    // parse string array as vector
    vector<int> trainingData = taskRequests[0].getTrainingData();

    // divide the vector into subvectors
    int numSubtasks = providerPeers.size();
    int subtaskSize = trainingData.size() / numSubtasks;
    int remainder = trainingData.size() % numSubtasks;

    string leaderUuid = taskRequests[0].getLeaderUuid();
    unordered_map<string, IpAddress> assignedFollowers =
        taskRequests[0].getAssignedFollowers();

    // create subvectors of requesttasks
    vector<TaskRequest> subtasks;
    for (int i = 0; i < numSubtasks; i++) {
        vector<int> subtaskData;
        for (int j = 0; j < subtaskSize; j++) {
            subtaskData.push_back(trainingData[i * subtaskSize + j]);
        }

        TaskRequest subtaskRequest = TaskRequest(subtaskData);
        subtaskRequest.setLeaderUuid(leaderUuid);
        subtaskRequest.setAssignedFollowers(assignedFollowers);
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
        subtaskRequest.setAssignedFollowers(
            taskRequests[0].getAssignedFollowers());
        taskRequests.push_back(subtaskRequest);
    }

    // remove the large task request
    taskRequests.erase(taskRequests.begin());
}

void Requester::send_task_request() {
    // divides the task into subtasks
    divide_task();

    // send the task request to the provider peers (leader and followers)
    int ctr = 0;
    for (auto peer : providerPeers) {
        // serialize the requests
        string serializedRequest = taskRequests[ctr].serialize();

        // set up the client
        const char* host = peer.second.ipAddress.c_str();
        const char* port = to_string(peer.second.port).c_str();
        client->setupConn(host, port, "tcp");

        // send the request
        client->sendRequest(serializedRequest.c_str());
        ctr++;
    }
}

void Requester::check_status() {}

TaskResponse Requester::get_results() {
    TaskResponse followerResult;

    // busy wait until connection is established
    // server->setupServer();
    while (true) {
        bool connStatus = server->acceptConn();
        if (connStatus) {
            // get data from followers and aggregate
            string msg = server->receiveFromConn();
            server->replyToConn("Received follower result.");
            server->closeConn();
            // deserialize into data
            followerResult.deserialize(msg);
            break;
        }
    }

    return followerResult;
}
