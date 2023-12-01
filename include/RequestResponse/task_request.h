#ifndef _TASK_REQUEST_H
#define _TASK_REQUEST_H
#include <cstring>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "../utility.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class TaskRequest {
    std::string leaderUuid;
    std::unordered_set<std::string> assignedPeers;
    std::vector<int> trainingData;

  public:
    TaskRequest(std::vector<int> trainingdata);

    void setLeaderUuid(std::string leaderUuid);
    void setAssignedPeers(std::unordered_set<std::string> assignedPeers);
    void setTrainingData(std::vector<int> trainingData);

    std::vector<int> getTrainingData() const;
    std::string getLeaderUuid() const;
    std::unordered_set<std::string> getAssignedPeers() const;

    std::string serialize() const;
    void deserialize(std::string msg);
};

#endif
