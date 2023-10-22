#ifndef _PEER_H
#define _PEER_H

#include <unordered_map>
#include <string>
#include <boost/asio/ip/address.hpp>

#include "utility.cpp"

class Peer {
    std::string uuid;
    boost::asio::ip::address ipAddress;
    unsigned short port;
    std::unordered_map<std::string, boost::asio::ip::address> providerPeers;
    
public:
    Peer(string, unsigned short) = 0;
}

#endif // _PEER_H
