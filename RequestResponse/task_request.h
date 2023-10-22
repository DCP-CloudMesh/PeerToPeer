#ifndef _TASK_REQUEST_H
#define _TASK_REQUEST_H

class TaskRequest {
  public:
    std::string leaderUuid;
    // PARTIITONED TRAINING DATA 
    std::unordered_set<std::string> assignedPeers;


}

#endif _TASK_REQUEST_H
