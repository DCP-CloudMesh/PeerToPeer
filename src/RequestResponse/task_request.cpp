#include "../../include/RequestResponse/task_request.h"

using namespace std;

TaskRequest::TaskRequest(std::string leaderUuid,
                         std::unordered_set<std::string> assignedPeers)
    : leaderUuid{leaderUuid}, assignedPeers{assignedPeers} {}

string TaskRequest::serializeRequest() const {
    string serializedRequest = "TaskRequest\n";
    serializedRequest += "Leader UUID: " + leaderUuid + "\n";
    serializedRequest += "Assigned Peers: ";
    for (auto peer : assignedPeers) {
        serializedRequest += peer + " ";
    }
    serializedRequest += "\n";
    return serializedRequest;
}