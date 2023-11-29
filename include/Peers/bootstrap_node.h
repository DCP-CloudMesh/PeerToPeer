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
    ~BootstrapNode();

    void listen_for_requests();
    void discovery();
};

#endif // _BOOTSTRAP_NODE_H
