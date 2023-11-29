#ifndef _DISCOVERY_
#define _DISCOVERY_

#include <string>
#include <unordered_map>

struct DiscoveryRequest {
    std::string req_uuid;
    std::string req_ipAddress;
    unsigned short req_port;
    int peers_requested;
};

struct DiscoveryResponse {
    std::unordered_map<std::string, std::string> providerPeers;
};

#endif
