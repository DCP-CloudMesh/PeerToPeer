#ifndef _SERVER_H
#define _SERVER_H

#include "../utility.h"
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>

class Server {
    const char* HOST;
    const char* PORT;
    const char* TYPE;
    IpAddress publicIP;
    int server; // stores the current running server id
  public:
    Server(const char* host, const char* port, const char* type);
    ~Server() {
        if (server != -1) {
            close(server);
        }
    };
    void setupServer();
    void acceptConn();
    void processClient(int connection);
};

#endif // _SERVER_H
