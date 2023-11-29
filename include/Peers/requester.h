#ifndef _REQUESTER_H_
#define _REQUESTER_H_

#include "peer.h"
#include "../RequestResponse/task_request.h"
#include "../RequestResponse/task_response.h"
#include "../Networking/client.h"

class Requester : protected Peer {
    TaskRequest request;
    void send_discovery_request();

  public:
    Requester(const char* host, const char* port);
    virtual ~Requester() noexcept;
    void set_task_request(TaskRequest);
    void send_task_request();
    void check_status();
    TaskResponse get_results();
};

#endif // _REQUESTER_H_
