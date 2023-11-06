#ifndef _REQUESTER_H_
#define _REQUESTER_H_

#include "peer.h"
#include "task_request.h"

class Requester : public Peer {
    TaskRequest request;

public:
    Requester();
    void send_discovery_request();
    void send_task_request();
};

#endif // _REQUESTER_H_
