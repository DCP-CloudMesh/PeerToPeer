#include "../../include/Peers/bootstrap_node.h"
using namespace std;

BootstrapNode::BootstrapNode(string uuid, unsigned short port) {}
BootstrapNode::~BootstrapNode() {}

string BootstrapNode::getServerIpAddress() { return "8.tcp.ngrok.io"; }
unsigned short BootstrapNode::getServerPort() { return 8080; }

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

string BootstrapNode::getFollowerIpAddress() { return "8.tcp.ngrok.io"; }
unsigned short BootstrapNode::getFollowerPort() { return 8080; }
