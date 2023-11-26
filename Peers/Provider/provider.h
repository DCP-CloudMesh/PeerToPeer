#ifndef _PROVIDER_H_
#define _PROVIDER_H_

#include "../../RequestResponse/task_request.h"
#include "../Peer/peer.h"
#include "../../Networking/Client/client.h"
#include "../../Networking/Server/server.h"

class Provider : public Peer {
    bool isBusy;
    TaskRequest task;
    bool isLocalBootstrap;
    std::string getPublicIPAddr();

  public:
    Provider(const char* host, const char* port);
};

#endif
