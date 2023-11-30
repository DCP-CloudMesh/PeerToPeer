#ifndef _PROVIDER_H_
#define _PROVIDER_H_

#include "../Networking/client.h"
#include "../Networking/server.h"
#include "../RequestResponse/task_request.h"
#include "peer.h"
#include <memory>

class Provider : public Peer {
    bool isBusy;
    std::unique_ptr<TaskRequest> task;
    bool isLocalBootstrap;
    std::string getPublicIPAddr();

  public:
    Provider(unsigned short port);
    void listen();
};

#endif
