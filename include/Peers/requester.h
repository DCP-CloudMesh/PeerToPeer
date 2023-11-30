#ifndef _REQUESTER_H_
#define _REQUESTER_H_

#include "../Networking/client.h"
#include "../RequestResponse/task_request.h"
#include "../RequestResponse/task_response.h"
#include "../utility.h"
#include "peer.h"
#include <sstream>
#include <vector>

class Requester : protected Peer {
    std::vector<TaskRequest> taskRequests;
    void divide_task();

  public:
    Requester(unsigned short port);
    ~Requester() noexcept;
    void set_task_request(TaskRequest taskRequest);
    void send_task_request();
    void send_discovery_request();
    void check_status();
    TaskResponse get_results();
};

#endif // _REQUESTER_H_
