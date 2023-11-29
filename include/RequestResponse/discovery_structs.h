#ifndef _DISCOVERY_
#define _DISCOVERY_

#include <string>
#include <unordered_map>
#include <boost/asio.hpp>

struct DiscoveryRequest {
    std::string req_uuid;
    boost::asio::ip::address req_ipAddress;
    unsigned short req_port;
    int peers_requested;
};

struct DiscoveryResponse {
    std::unordered_map<std::string, boost::asio::ip::address> providerPeers;
};

#endif
