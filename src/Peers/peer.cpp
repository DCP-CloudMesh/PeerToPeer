#include "../../include/Peers/peer.h"

// #include "../../utility.h"

using namespace std;

Peer::Peer(const char* host, const char* port) : host(host), port(port){
    const char* type = "tcp";
    this->server = new Server(host, port, type);
    this->client = new Client();
}

Peer::~Peer() {}
