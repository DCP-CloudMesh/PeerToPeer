#include "peer.h"

using namespace std;

Peer::Peer(string uuid, string ipAddress, unsigned short port) {
    this->uuid = uuid;
    this->ipAddress.ipAddress = ipAddress;
    this->ipAddress.port = port;
}

// implementation for virtual destructor
Peer::~Peer() {}
