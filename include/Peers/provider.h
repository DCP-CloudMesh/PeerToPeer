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

  public:
    Provider(const char* port, std::string uuid);
    ~Provider() noexcept;

    void registerWithBootstrap();
    void listen();
    void leaderHandleTaskRequest(const IpAddress& requesterIpAddr);
    void followerHandleTaskRequest();
    void processData();
    TaskResponse processWorkload();
    TaskResponse aggregateResults(std::vector<std::vector<int>> followerData);
};

#endif
