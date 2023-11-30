#ifndef __UTILITY__
#define __UTILITY__

#include <iostream>
#include <random>
#include <sstream>

struct IpAddress {
    std::string ipAddress;
    unsigned short port;
};

namespace uuid {
static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<> dis(0, 15);
static std::uniform_int_distribution<> dis2(8, 11);

std::string generate_uuid_v4();
} // namespace uuid

std::string startNgrokForwarding(unsigned short port);

#endif // __UTILITY__
