#ifndef _PEER_H
#define _PEER_H

#include <string>
#include <unordered_map>

#include "../../utility.h"
#include "../../Networking/Client/client.h"
#include "../../Networking/Server/server.h"

// struct IpAddress;

class Peer {
    const char* host;
    const char* port;
    
  protected:
    Server *server;
    Client *client;
    // maps uuid to ip address
    std::unordered_map<std::string, IpAddress> providerPeers;

  public:
    Peer(const char* host, const char* p);
    virtual ~Peer();
};

#endif // _PEER_H
