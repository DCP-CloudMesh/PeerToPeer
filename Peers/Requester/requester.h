#ifndef _REQUESTER_H_
#define _REQUESTER_H_

#include "../Peer/peer.h"
#include "../../RequestResponse/task_request.h"
#include "../../RequestResponse/task_response.h"
#include "../../Networking/Client/client.h"

class Requester : protected Peer {
    TaskRequest request;
    void send_discovery_request();

  public:
    Requester(Server, Client);
    virtual ~Requester() noexcept;
    void set_task_request(TaskRequest);
    void send_task_request();
    void check_status();
    TaskResponse get_results();
};

#endif // _REQUESTER_H_
