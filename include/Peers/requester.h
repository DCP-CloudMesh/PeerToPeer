#ifndef _REQUESTER_H_
#define _REQUESTER_H_

#include "../Networking/client.h"
#include "../RequestResponse/task_request.h"
#include "../RequestResponse/task_response.h"
#include "../utility.h"
#include "peer.h"

class Requester : protected Peer {
    std::string serializedRequest;
    void send_discovery_request();

  public:
    Requester();
    ~Requester() noexcept;
    void set_task_request(TaskRequest taskRequest);
    void send_task_request();
    void check_status();
    TaskResponse get_results();
};

#endif // _REQUESTER_H_
