#include "../../include/RequestResponse/task_request.h"

using namespace std;

TaskRequest::TaskRequest(vector<int> trainingData)
    : trainingData{trainingData} {}

void TaskRequest::setLeaderUuid(std::string leaderUuid) {
    this->leaderUuid = leaderUuid;
}

void TaskRequest::setAssignedPeers(
    std::unordered_set<std::string> assignedPeers) {
    this->assignedPeers = assignedPeers;
}

void TaskRequest::setTrainingData(vector<int> trainingData) {
    this->trainingData = trainingData;
}

vector<int> TaskRequest::getTrainingData() const { return trainingData; }

string TaskRequest::getLeaderUuid() const { return leaderUuid; }

unordered_set<string> TaskRequest::getAssignedPeers() const {
    return assignedPeers;
}

std::string TaskRequest::serialize() const {
    json j;
    j["leaderUuid"] = leaderUuid;
    j["assignedPeers"] = assignedPeers;
    j["trainingData"] = trainingData;
    return j.dump();
}

void TaskRequest::deserialize(std::string msg) {
    json j = json::parse(msg);
    leaderUuid = j["leaderUuid"];
    assignedPeers = j["assignedPeers"];
    // Explicitly convert the JSON array to std::vector<int>
    trainingData = j["trainingData"].get<std::vector<int>>();
}