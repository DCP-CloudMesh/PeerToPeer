#ifndef _CLIENT_H
#define _CLIENT_H

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class Client {
    int CONN;

  public:
    Client();
    ~Client();
    int setUpConn(const char* HOST, const char* PORT, const char* TYPE);
    int send(const char* data);
};

#endif // _CLIENT_H
