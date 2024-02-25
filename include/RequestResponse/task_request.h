#ifndef _TASK_REQUEST_H
#define _TASK_REQUEST_H

#include <string>
#include <vector>

#include "payload.h"
#include "../utility.h"

class TaskRequest : public Payload {
    unsigned int numWorkers;
    std::string leaderUuid;
    AddressTable assignedWorkers;
    std::vector<int> trainingData;

  public:
    TaskRequest();
    TaskRequest(const unsigned int numWorkers,
                const std::vector<int>& trainingdata);

    void setLeaderUuid(const std::string& leaderUuid);
    void setAssignedWorkers(const AddressTable& assignedWorkers);
    void setTrainingData(const std::vector<int>& trainingData);

    unsigned int getNumWorkers() const;
    std::vector<int> getTrainingData() const;
    std::string getLeaderUuid() const;
    AddressTable getAssignedWorkers() const;

    std::string serialize() const override;
    void deserialize(const std::string& serializedData) override;
};

#endif
