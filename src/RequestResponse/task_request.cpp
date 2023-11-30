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

string TaskRequest::serialize() const {
    string serializedRequest = "TaskRequest\n";
    serializedRequest += "LeaderUuid: " + leaderUuid + "\n";
    serializedRequest += "AssignedPeers:";
    for (auto peer : assignedPeers) {
        serializedRequest += " " + peer;
    }
    serializedRequest += "\n";
    serializedRequest += "TrainingData: " + vectorToString(trainingData) + "\n";
    return serializedRequest;
}

void TaskRequest::deserialize(string msg) {
    stringstream ss(msg);
    // Ignore the initial "TaskRequest" part
    ss.ignore(numeric_limits<streamsize>::max());

    // LeaderUuid
    ss.ignore(numeric_limits<streamsize>::max(), ':');
    ss >> leaderUuid;

    // AssignedPeers
    ss.ignore(numeric_limits<streamsize>::max(), ':');
    string peer;
    while (getline(ss, peer, ' ')) {
        assignedPeers.insert(peer);
    }

    // TrainingData
    ss.ignore(numeric_limits<streamsize>::max(), ':');
    string element;
    while (getline(ss, element, ',')) {
        trainingData.push_back(stoi(element));
    }
}
