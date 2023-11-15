#include "discovery_structs.h"

std::string serializeDiscoveryRequest(const DiscoveryRequest& request) {
    std::string serializedData = request.req_uuid + "|" +
                                 request.req_ipAddress.to_string() + "|" +
                                 std::to_string(request.req_port) + "|" +
                                 std::to_string(request.peers_requested);
}

DiscoveryRequest
deserializeDiscoveryRequest(const std::string& serializedData) {
    DiscoveryRequest request;
    size_t pos = 0;
    size_t prevPos = 0;
    for (int i = 0; i < 4; ++i) {
        pos = serializedData.find('|', prevPos);
        std::string token = serializedData.substr(prevPos, pos - prevPos);
        prevPos = pos + 1;
        switch (i) {
        case 0:
            request.req_uuid = token;
            break;
        case 1:
            request.req_ipAddress =
                boost::asio::ip::address_v4::from_string(token);
            break;
        case 2:
            request.req_port = std::stoi(token);
            break;
        case 3:
            request.peers_requested = std::stoi(token);
            break;
        }
    }
    return request;
}
