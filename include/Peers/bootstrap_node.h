#ifndef _BOOTSTRAP_NODE_H
#define _BOOTSTRAP_NODE_H

#include <string>
#include <unordered_map>

class BootstrapNode {
    // if inherited from peer, eliminate:
    std::string uuid;
    std::string ipAddress;
    unsigned short port;
    std::unordered_map<std::string, std::string> providerPeers;
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
};

#endif // _BOOTSTRAP_NODE_H
