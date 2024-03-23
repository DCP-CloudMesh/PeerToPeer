#include "../../include/Peers/requester.h"
#include "../../include/Peers/bootstrap_node.h"
#include "../../include/RequestResponse/message.h"
#include "../../include/RequestResponse/generic_response.h"
#include "../../include/RequestResponse/discovery_request.h"
#include "../../include/RequestResponse/discovery_response.h"
#include "../../include/utility.h"

using namespace std;

Requester::Requester(const char* port) : Peer() {
    setupServer("127.0.0.1", port);
}

Requester::~Requester() noexcept {}

void Requester::sendDiscoveryRequest(unsigned int numProviders) {
    const char* bootstrapHost = BootstrapNode::getServerIpAddress();
    const char* bootstrapPort = BootstrapNode::getServerPort();
    cout << "Connecting to bootstrap node at "
         << bootstrapHost << ":" << bootstrapPort << endl;
    client->setupConn(bootstrapHost, bootstrapPort, "tcp");

    shared_ptr<Payload> payload = make_shared<DiscoveryRequest>(numProviders);
    Message msg(uuid, IpAddress(host, port), payload);

    client->sendMsg(msg.serialize().c_str());
}

void Requester::waitForDiscoveryResponse() {
    cout << "Waiting for discovery response..." << endl;
    while (!server->acceptConn());

    // receive response from bootstrap (or possibly another peer)
    string serializedData = server->receiveFromConn();
    // process response
    string replyPrefix = "Requester (" + uuid + ") - ";
    Message msg;
    msg.deserialize(serializedData);
    shared_ptr<Payload> payload = msg.getPayload();

    if (payload->getType() == Payload::Type::DISCOVERY_RESPONSE) {
        shared_ptr<DiscoveryResponse> dr =
            static_pointer_cast<DiscoveryResponse>(payload);
        AddressTable availablePeers = dr->getAvailablePeers();
        for (auto & it : availablePeers) {
            providerPeers[it.first] = it.second;
        }
        string logMsg = "Received " + to_string(availablePeers.size()) +
                        " peers in discovery response";
        cout << logMsg << endl;
        server->replyToConn(replyPrefix + logMsg);
    }
    server->closeConn();
}

void Requester::setTaskRequest(TaskRequest request_) {
    // push large task request into the vector
    taskRequests.push_back(request_);
}

void Requester::divideTask() {
    // TODO: use deque (dividing into subtasks should remain at front of queue)

    // divide the large task into subtasks
    // divide "[2, 1, 4, 3, 6, 5, 9, 7, 8, 10]" into as many subtasks as
    // there
    TaskRequest queuedTask = taskRequests[0];

    // parse string array as vector
    vector<int> trainingData = queuedTask.getTrainingData();

    // divide the vector into subvectors
    int numSubtasks = queuedTask.getNumWorkers();
    int subtaskSize = trainingData.size() / numSubtasks;
    int remainder = trainingData.size() % numSubtasks;

    string leaderUuid = queuedTask.getLeaderUuid();
    AddressTable assignedWorkers = queuedTask.getAssignedWorkers();

    // create subvectors of requesttasks
    vector<TaskRequest> subtasks;
    for (int i = 0; i < numSubtasks; i++) {
        vector<int> subtaskData;
        for (int j = 0; j < subtaskSize; j++) {
            subtaskData.push_back(trainingData[i * subtaskSize + j]);
        }

        TaskRequest subtaskRequest = TaskRequest(1, subtaskData);
        subtaskRequest.setLeaderUuid(leaderUuid);
        subtaskRequest.setAssignedWorkers(assignedWorkers);
        taskRequests.push_back(subtaskRequest);
    }

    // add the remainder to the last subtask
    if (remainder != 0) {
        vector<int> subtaskData;
        for (int i = 0; i < remainder; i++) {
            subtaskData.push_back(trainingData[numSubtasks * subtaskSize + i]);
        }

        TaskRequest subtaskRequest = TaskRequest(1, subtaskData);
        subtaskRequest.setLeaderUuid(queuedTask.getLeaderUuid());
        subtaskRequest.setAssignedWorkers(queuedTask.getAssignedWorkers());
        taskRequests.push_back(subtaskRequest);
    }

    // remove the large task request
    taskRequests.erase(taskRequests.begin());
}

void Requester::sendTaskRequest() {
    // Ensure connected to sufficient number of provider peers
    unsigned int numRequestedWorkers = taskRequests[0].getNumWorkers();
    while (true) {
        cout << "Insufficient number of connected provider peers" << endl
             << "Sending out discovery request..." << endl;
        sendDiscoveryRequest(numRequestedWorkers);
        waitForDiscoveryResponse();
        if (providerPeers.size() >= numRequestedWorkers) break;
        sleep(5);
    }

    // Set task leader and followers
    AddressTable workers{};
    for (auto & provider : providerPeers) {
        if (workers.size() == numRequestedWorkers) {
            break;
        }
        workers[provider.first] = provider.second;
    }
    taskRequests[0].setAssignedWorkers(workers);
    taskRequests[0].setLeaderUuid(workers.begin()->first);

    // divides the task into subtasks
    divideTask();

    // send the task request to the workers
    int ctr = 0;
    for (auto & worker : workers) {
        // package and serialize the requests
        shared_ptr<TaskRequest> payload =
            make_shared<TaskRequest>(taskRequests[ctr]);
        Message msg(uuid, IpAddress(host, port), payload);

        // set up the client
        const char* host = worker.second.host.c_str();
        const char* port = to_string(worker.second.port).c_str();
        client->setupConn(host, port, "tcp");

        // send the request
        client->sendMsg(msg.serialize().c_str());
        ctr++;
    }
}

void Requester::checkStatus() {}

TaskResponse Requester::getResults() {
    TaskResponse taskResult;
    // busy wait until connection is established
    while (!server->acceptConn());

    // get data from workers and aggregate
    string serializedData = server->receiveFromConn();
    server->replyToConn("Received task result.");
    server->closeConn();

    // deserialize into data
    Message msg;
    msg.deserialize(serializedData);
    IpAddress leaderIpAddr = msg.getSenderIpAddr();
    shared_ptr<TaskResponse> taskRespPtr =
        static_pointer_cast<TaskResponse>(msg.getPayload());
    taskResult = std::move(*taskRespPtr); // transfer data

    // send success acknowledgement to provider
    shared_ptr<GenericResponse> payload =
        make_shared<GenericResponse>(GenericResponse::Status::SUCCESS);
    Message response(uuid, IpAddress(host, port), payload);
    client->setupConn(leaderIpAddr, "tcp");
    client->sendMsg(response.serialize().c_str());

    return taskResult;
}
