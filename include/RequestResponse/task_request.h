#ifndef _TASK_REQUEST_H
#define _TASK_REQUEST_H
#include <string>
#include <unordered_set>

class TaskRequest {
    std::string leaderUuid;
    // PARTIITONED TRAINING DATA
    std::unordered_set<std::string> assignedPeers;

  public:
    TaskRequest(std::string leaderUuid,
                std::unordered_set<std::string> assignedPeers);

    std::string serializeRequest() const;
};

#endif
