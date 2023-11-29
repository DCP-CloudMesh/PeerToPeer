#ifndef _PROVIDER_H_
#define _PROVIDER_H_

#include "../RequestResponse/task_request.h"
#include "peer.h"
#include "../Networking/client.h"
#include "../Networking/server.h"

class Provider : public Peer {
    bool isBusy;
    TaskRequest task;
    bool isLocalBootstrap;
    std::string getPublicIPAddr();

  public:
    Provider(const char* host, const char* port);
};

#endif
