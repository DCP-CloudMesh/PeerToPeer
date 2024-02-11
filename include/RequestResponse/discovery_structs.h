#ifndef _DISCOVERY_
#define _DISCOVERY_

#include <string>
#include "../utility.h"

struct DiscoveryRequest {
    std::string req_uuid;
    std::string req_ipAddress;
    unsigned short req_port;
    int peers_requested;
};

struct DiscoveryResponse {
    AddressTable providerPeers;
};

#endif
