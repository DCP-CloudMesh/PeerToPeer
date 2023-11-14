#ifndef _SERVER_H
#define _SERVER_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class Server {
    const char* HOST;
    const char* PORT;
    const char* TYPE;

  public:
    Server(const char* host, const char* port, const char* type);
};

#endif // _SERVER_H