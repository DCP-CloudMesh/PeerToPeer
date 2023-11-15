#ifndef _PEER_H
#define _PEER_H

#include "../Networking/Client/client.h"
#include "../Networking/Server/server.h"

#include "../utility.cpp"
#include <string>
#include <unordered_map>

class Peer {
    Server server;
    Client client;

  protected:
    // maps uuid to ip address
    std::unordered_map<std::string, IpAddress> providerPeers;

  public:
    Peer(Server, Client);
    virtual ~Peer();
};

#endif // _PEER_H
