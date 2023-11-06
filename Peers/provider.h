#ifndef _PROVIDER_H_
#define _PROVIDER_H_

#include "peer.h"
#include "../RequestResponse/task_request.h"

class Provider : public Peer {
    bool isBusy;
    TaskRequest task;
    bool isLocalBootstrap;

public:
    Provider();
}

#endif
