#ifndef _TASK_RESPONSE_H
#define _TASK_RESPONSE_H
#include <string>
#include <unordered_set>

#include "../utility.h"

class TaskResponse {
    std::vector<int> trainingData;

  public:
    TaskResponse() {}
    TaskResponse(std::vector<int> trainingData);
    std::vector<int> getTrainingData() const;
    void setTrainingData(std::vector<int> trainingData);

    std::string serialize() const;
    void deserialize(std::string msg);
};

#endif
