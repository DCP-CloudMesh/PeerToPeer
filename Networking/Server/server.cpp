#include "server.h"

Server::Server(const char* host, const char* port, const char* type)
    : HOST{host}, PORT{port}, TYPE{type} {}
