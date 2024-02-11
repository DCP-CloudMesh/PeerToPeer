#ifndef _TASK_REQUEST_H
#define _TASK_REQUEST_H
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

#include "../utility.h"

class TaskRequest {
    std::string leaderUuid;
    AddressTable assignedFollowers;
    std::vector<int> trainingData;

  public:
    TaskRequest(std::vector<int> trainingdata);

    void setLeaderUuid(std::string leaderUuid);
    void setAssignedFollowers(AddressTable assignedFollowers);
    void setTrainingData(std::vector<int> trainingData);

    std::vector<int> getTrainingData() const;
    std::string getLeaderUuid() const;
    AddressTable getAssignedFollowers() const;

    std::string serialize() const;
    void deserialize(std::string msg);
};

#endif
