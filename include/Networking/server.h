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
    const char* CONNTYPE;
    IpAddress publicIP;
    int server;     // stores the current running server id
    int activeConn; // stores the current active connection id

  public:
    Server(const char* host, const char* port, const char* type);
    ~Server() {
        if (server != -1) {
            close(server);
        }
    };
    void setupServer();                    // prepare server for connection
    bool acceptConn();                     // blocking
    std::string receiveFromConn();         // process the active conn
    void replyToConn(std::string message); // process the active conn
    void closeConn();                      // close the active conn
};

#endif // _SERVER_H
