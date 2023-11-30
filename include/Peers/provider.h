#ifndef _PROVIDER_H_
#define _PROVIDER_H_

#include "../Networking/client.h"
#include "../Networking/server.h"
#include "../RequestResponse/task_request.h"
#include "../RequestResponse/task_response.h"

#include "peer.h"
#include <memory>
#include <thread>
#include <vector>

class Provider : public Peer {
    bool isBusy;
    bool isLocalBootstrap;
    bool isLeader;
    std::unique_ptr<TaskRequest> task;
    std::string getPublicIPAddr();

  public:
    Provider(unsigned short port);
    void listen();
    void processData();
    void processWorkload(); // worker function to manipulate the TaskRequest
    TaskRequest aggregateResults(std::vector<std::vector<int>> followerData);
};

#endif
