#ifndef _CLIENT_H
#define _CLIENT_H

class Client {
  public:
    Client();
    virtual ~Client();
    int setUpConn(const char* HOST, const char* PORT, const char* TYPE);
    void request():
};

#endif // _CLIENT_H
