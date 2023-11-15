#ifndef _PEER_H
#define _PEER_H

#include <string>
#include <unordered_map>

#include "../utility.cpp"

class Peer {
    std::string uuid;
    IpAddress ipAddress;

  protected:
    // maps uuid to ip address
    std::unordered_map<std::string, IpAddress> providerPeers;

  public:
    Peer(std::string uuid, std::string ipAddress, unsigned short port);
    virtual ~Peer();
};

#endif // _PEER_H
