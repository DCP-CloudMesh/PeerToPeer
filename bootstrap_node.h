#ifndef _BOOTSTRAP_NODE_H
#define _BOOTSTRAP_NODE_H

#include <string>

class BootstrapNode {
    // if inherited from peer, eliminate:
    std::string uuid;
    boost::asio::ip::address ipAddress;
    unsigned short port;
    std::unordered_map<std::string, boost::asio::ip::address> providerPeers;
    // end if inherited from peer

  public:
    BootstrapNode(std::string, unsigned short);
    ~BootstrapNode();

    void listen_for_requests();
    void discovery();
};

#endif _BOOTSTRAP_NODE_H
