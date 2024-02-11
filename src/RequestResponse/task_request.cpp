#include "../../include/RequestResponse/task_request.h"
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;

TaskRequest::TaskRequest(vector<int> trainingData)
    : trainingData{trainingData} {}

void TaskRequest::setLeaderUuid(std::string leaderUuid) {
    this->leaderUuid = leaderUuid;
}

void TaskRequest::setAssignedFollowers(
    std::unordered_map<std::string, IpAddress> assignedFollowers) {
    this->assignedFollowers = assignedFollowers;
}

void TaskRequest::setTrainingData(vector<int> trainingData) {
    this->trainingData = trainingData;
}

vector<int> TaskRequest::getTrainingData() const { return trainingData; }

string TaskRequest::getLeaderUuid() const { return leaderUuid; }

std::unordered_map<std::string, IpAddress>
TaskRequest::getAssignedFollowers() const {
    return assignedFollowers;
}

std::string TaskRequest::serialize() const {
    json j;
    j["leaderUuid"] = leaderUuid;
    // Convert std::unordered_map to JSON object
    for (const auto& entry : assignedFollowers) {
        j["assignedFollowers"][entry.first] = serializeIpAddress(entry.second);
    }
    j["trainingData"] = trainingData;
    return j.dump();
}

void TaskRequest::deserialize(std::string msg) {
    try {
        json j = json::parse(msg);
        if (j.contains("leaderUuid"))
            leaderUuid = j["leaderUuid"].get<std::string>();

        if (j.contains("assignedFollowers")) {
            assignedFollowers.clear(); // Clear existing data
            auto followersJson = j["assignedFollowers"];
            for (auto it = followersJson.begin(); it != followersJson.end();
                 ++it) {
                assignedFollowers[it.key()] =
                    deserializeIpAddress(it.value());
            }   
        }

        if (j.contains("trainingData"))
            trainingData = j["trainingData"].get<std::vector<int>>();

    } catch (json::exception& e) {
        cout << "JSON parsing error: " << e.what() << endl;
    }
}