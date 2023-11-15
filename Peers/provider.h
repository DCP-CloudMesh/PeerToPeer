#ifndef _PROVIDER_H_
#define _PROVIDER_H_

#include "../RequestResponse/task_request.h"
#include "peer.h"

class Provider : public Peer {
    bool isBusy;
    TaskRequest task;
    bool isLocalBootstrap;
    string getPublicIPAddr();

  public:
    Provider();
}

#endif
