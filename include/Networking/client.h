#ifndef _CLIENT_H
#define _CLIENT_H

class Client {
  int CONN;
  public:
    Client();
    ~Client();
    int setUpConn(const char* HOST, const char* PORT, const char* TYPE);
    int request(const char* data);
};

#endif // _CLIENT_H
