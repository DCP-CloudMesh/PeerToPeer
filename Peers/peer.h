#ifndef _PEER_H
#define _PEER_H

#include <string>
#include <unordered_map>

#include "../utility.cpp"



class Peer {
    std::string uuid;
    std::string ipAddress;
    unsigned short port;

   protected:
    // maps uuid to ip address
    std::unordered_map<std::string, std::string> providerPeers;

   public:
    Peer(std::string uuid, std::string ipAddress, unsigned short port);
    virtual ~Peer();
};

#endif  // _PEER_H
