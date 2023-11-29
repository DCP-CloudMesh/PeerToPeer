#ifndef _TASK_REQUEST_H
#define _TASK_REQUEST_H
#include <string>
#include <unordered_set>

class TaskRequest {
  public:
    std::string leaderUuid;
    // PARTIITONED TRAINING DATA
    std::unordered_set<std::string> assignedPeers;
};

#endif
