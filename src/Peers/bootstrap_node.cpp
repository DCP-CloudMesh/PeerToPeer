#include "../../include/Peers/bootstrap_node.h"

BootstrapNode::BootstrapNode(std::string uuid, unsigned short port) {}

std::string BootstrapNode::getServerIpAddress() { return "8.tcp.ngrok.io"; }
unsigned short BootstrapNode::getServerPort() { return 8080; }

std::string BootstrapNode::getLeaderIpAddress() { return "8.tcp.ngrok.io"; }
unsigned short BootstrapNode::getLeaderPort() { return 8080; }

std::string BootstrapNode::getFollowerIpAddress() { return "8.tcp.ngrok.io"; }
unsigned short BootstrapNode::getFollowerPort() { return 8080; }
