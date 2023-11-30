#include "../../include/Peers/provider.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

Provider::Provider(unsigned short port) : Peer() {
    isBusy = false;
    isLocalBootstrap = false;

    setupServer("", to_string(port).c_str());
}

void Provider::listen() { server->acceptConn(); }
