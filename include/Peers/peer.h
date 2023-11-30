#ifndef _PEER_H
#define _PEER_H

#include <string>
#include <unordered_map>

#include "../Networking/client.h"
#include "../Networking/server.h"
#include "../utility.h"

class Peer {
  protected:
    const char* host;
    const char* port;
    std::string uuid;

    Server* server;
    Client* client;
    // maps uuid to ip address
    std::unordered_map<std::string, IpAddress> providerPeers;
    IpAddress leaderIP;

  public:
    Peer();
    void setupServer(const char* host, const char* port);
    virtual ~Peer();
};

#endif // _PEER_H
