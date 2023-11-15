#include "requester.h"
using namespace std;

Requester::Requester(Server server, Client client) : Peer(server, client) {}

Requester::~Requester() {
    // additional code here
}
void Requester::set_task_request(TaskRequest request_) { request = request_; }

void Requester::send_discovery_request() {
    // additional code here
}

void Requester::send_task_request() {
    for (const auto& peer : providerPeers) {
        // additional code here
    }
}
