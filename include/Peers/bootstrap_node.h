#ifndef _BOOTSTRAP_NODE_H
#define _BOOTSTRAP_NODE_H

#include <string>

#include "../utility.h"

class BootstrapNode {
    // if inherited from peer, eliminate:
    std::string uuid;
    std::string ipAddress;
    unsigned short port;
    AddressTable providerPeers;
    // end if inherited from peer

  public:
    BootstrapNode(std::string, unsigned short);
    // ----------------- FIX LATER -----------------
    BootstrapNode() {}
    ~BootstrapNode();

    void listenForRequests();
    void discovery();

    std::string getServerIpAddress();
    unsigned short getServerPort();

    std::string getLeaderIpAddress();
    unsigned short getLeaderPort();
    std::string getLeaderUuid();

    std::string getFollowerIpAddress();
    unsigned short getFollowerPort();
    std::string getFollowerUuid();
};

#endif // _BOOTSTRAP_NODE_H
