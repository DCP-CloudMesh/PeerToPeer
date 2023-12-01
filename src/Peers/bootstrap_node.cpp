#include "../../include/Peers/bootstrap_node.h"
using namespace std;

BootstrapNode::BootstrapNode(string uuid, unsigned short port) {}
BootstrapNode::~BootstrapNode() {}

string BootstrapNode::getServerIpAddress() {
    string ip;
#if defined(NOLOCAL)
    ip = "8.tcp.ngrok.io";
#elif defined(LOCAL)
    ip = "127.0.0.1";
#endif
    return ip;
}
unsigned short BootstrapNode::getServerPort() {
    unsigned short port;
#if defined(NOLOCAL)
    port = 12701;
#elif defined(LOCAL)
    port = 8082;
#endif
    return port;
}

string BootstrapNode::getLeaderIpAddress() {
    string ip;
#if defined(NOLOCAL)
    ip = "8.tcp.ngrok.io";
#elif defined(LOCAL)
    ip = "127.0.0.1";
#endif
    return ip;
}
unsigned short BootstrapNode::getLeaderPort() {
    unsigned short port;
#if defined(NOLOCAL)
    port = 12701;
#elif defined(LOCAL)
    port = 8080;
#endif
    return port;
}
string BootstrapNode::getLeaderUuid() { return "1"; }

string BootstrapNode::getFollowerIpAddress() {
    string ip;
#if defined(NOLOCAL)
    ip = "8.tcp.ngrok.io";
#elif defined(LOCAL)
    ip = "127.0.0.1";
#endif
    return ip;
}
unsigned short BootstrapNode::getFollowerPort() {
    unsigned short port;
#if defined(NOLOCAL)
    port = 12701;
#elif defined(LOCAL)
    port = 8081;
#endif
    return port;
}

string BootstrapNode::getFollowerUuid() { return "2"; }
