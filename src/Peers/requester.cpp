#include "../../include/Peers/requester.h"

using namespace std;

Requester::Requester() : Peer() { 
    // setupServer("", "8080"); 
}

Requester::~Requester() noexcept {}

void Requester::set_task_request(TaskRequest request_) {
    serializedRequest = request_.serializeRequest();
}

void Requester::send_discovery_request() {
    // update the member hash map

    leaderIP = IpAddress{"0.tcp.ngrok.io", 10904};
}

void Requester::send_task_request() {
    // additional code here
    // client = new Client(host, port);
    const char* host = leaderIP.ipAddress.c_str();
    const char* port = std::to_string(leaderIP.port).c_str();
    client->setUpConn(host, port, "tcp");
    client->sendRequest(serializedRequest.c_str());
}

void Requester::check_status() {}

TaskResponse Requester::get_results() { return TaskResponse(); }
