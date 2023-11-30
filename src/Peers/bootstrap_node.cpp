#include "../../include/Peers/bootstrap_node.h"

BootstrapNode::BootstrapNode(std::string uuid, unsigned short port) {}
BootstrapNode::~BootstrapNode() {}

std::string BootstrapNode::getServerIpAddress() { return "8.tcp.ngrok.io"; }
unsigned short BootstrapNode::getServerPort() { return 8080; }

std::string BootstrapNode::getLeaderIpAddress() { return "0.tcp.ngrok.io"; }
unsigned short BootstrapNode::getLeaderPort() { return 17700; }
std::string BootstrapNode::getLeaderUuid() { return "1"; }

std::string BootstrapNode::getFollowerIpAddress() { return "8.tcp.ngrok.io"; }
unsigned short BootstrapNode::getFollowerPort() { return 8080; }
