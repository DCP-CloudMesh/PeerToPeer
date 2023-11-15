#ifndef _REQUESTER_H_
#define _REQUESTER_H_

#include "peer.h"
#include "task_request.h"

class Requester : protected Peer {
    TaskRequest request;
    void send_discovery_request();
    void send_task_request();

  public:
    Requester(Server, Client);
    virtual ~Requester() noexcept;
    void set_task_request(TaskRequest);
};

#endif // _REQUESTER_H_
