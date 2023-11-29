#include "../../include/Peers/provider.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

Provider::Provider(const char* host, const char* port) : Peer(host, port) {
    this->isBusy = false;
    this->isLocalBootstrap = false;
}
