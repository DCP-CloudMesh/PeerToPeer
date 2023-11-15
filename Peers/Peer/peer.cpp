#include "peer.h"

using namespace std;

Peer::Peer(Server server, Client client) : server(server), client(client) {}

Peer::~Peer() {}
