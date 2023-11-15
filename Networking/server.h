#ifndef _SERVER_H
#define _SERVER_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <iostream>

class Server {
    const char* HOST;
    const char* PORT;
    const char* TYPE;

  public:
    Server(const char* host, const char* port, const char* type);
};

#endif // _SERVER_H