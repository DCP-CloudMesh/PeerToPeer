#include "../../include/RequestResponse/task_request.h"

using namespace std;
using namespace nlohmann;

TaskRequest::TaskRequest() : Payload(Type::TASK_REQUEST) {}
TaskRequest::TaskRequest(const unsigned int numWorkers,
                         const vector<int>& trainingData)
    : Payload(Type::TASK_REQUEST), numWorkers{numWorkers},
      trainingData{trainingData} {}

void TaskRequest::setLeaderUuid(const string& leaderUuid) {
    this->leaderUuid = leaderUuid;
}

void TaskRequest::setAssignedWorkers(const AddressTable& assignedWorkers) {
    this->assignedWorkers = assignedWorkers;
}

void TaskRequest::setTrainingData(const vector<int>& trainingData) {
    this->trainingData = trainingData;
}

unsigned int TaskRequest::getNumWorkers() const { return numWorkers; }

vector<int> TaskRequest::getTrainingData() const { return trainingData; }

string TaskRequest::getLeaderUuid() const { return leaderUuid; }

AddressTable TaskRequest::getAssignedWorkers() const {
    return assignedWorkers;
}

string TaskRequest::serialize() const {
    json j;
    j["numWorkers"] = numWorkers;
    j["leaderUuid"] = leaderUuid;
    // Convert unordered_map to JSON object
    for (const auto& entry : assignedWorkers) {
        j["assignedWorkers"][entry.first] = serializeIpAddress(entry.second);
    }
    j["trainingData"] = trainingData;
    return j.dump();
}

void TaskRequest::deserialize(const string& serializedData) {
    try {
        json j = json::parse(serializedData);
        numWorkers = j["numWorkers"].get<unsigned int>();
        leaderUuid = j["leaderUuid"].get<string>();
        trainingData = j["trainingData"].get<vector<int>>();

        assignedWorkers.clear(); // Clear existing data
        auto workersJson = j["assignedWorkers"];
        for (auto it = workersJson.begin(); it != workersJson.end(); ++it) {
            assignedWorkers[it.key()] = deserializeIpAddress(it.value());
        }
    } catch (json::exception& e) {
        cout << "JSON parsing error: " << e.what() << endl;
    }
}
