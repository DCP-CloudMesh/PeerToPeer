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
    int setupConn(const char* HOST, const char* PORT, const char* CONNTYPE);
    int sendRequest(const char* data);
};

#endif // _CLIENT_H
