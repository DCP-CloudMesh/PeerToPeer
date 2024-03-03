#include "../../include/Networking/client.h"

using namespace std;

Client::Client() : CONN{-1} {}

Client::~Client() {}

int Client::setupConn(const char* HOST, const char* PORT,
                      const char* CONNTYPE) {
    addrinfo hints, *serverInfo;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(HOST, PORT, &hints, &serverInfo) != 0) {
        cerr << "Error getting address info: " << gai_strerror(errno)
             << endl;
        return 1;
    }

    for (auto addr = serverInfo; addr != nullptr; addr = addr->ai_next) {
        CONN = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (CONN == -1) {
            cerr << "Error creating socket: " << strerror(errno)
                 << endl;
            continue;
        }

        if (connect(CONN, addr->ai_addr, addr->ai_addrlen) == -1) {
            cerr << "Error connecting: " << strerror(errno) << endl;
            close(CONN);
            CONN = -1;
            continue;
        }

        // If we reached here, the CONN was successful
        cout << "Connection successful." << endl;
        break;
    }

    freeaddrinfo(serverInfo);

    if (CONN == -1) {
        return -1;
    }
    return 0;
}

int Client::setupConn(const IpAddress& ipAddress, const char* CONNTYPE) {
    return setupConn(ipAddress.host.c_str(),
                     to_string(ipAddress.port).c_str(), CONNTYPE);
}

int Client::sendMsg(const char* data) {
    // retry if failed 5 times
    bool sent = false;
    for (int i = 0; i < 5; i++) {
        if (send(CONN, data, strlen(data), 0) == -1) {
            cerr << "Retrying sending request..." << endl;
        } else {
            sent = true;
            break;
        }
    }

    if (!sent) {
        cerr << "Error sending request: " << strerror(errno) << endl;
        close(CONN);
        return 1;
    }

    char buffer[1024];
    ssize_t mLen = recv(CONN, buffer, sizeof(buffer), 0);
    if (mLen < 0) {
        cerr << "Error reading: " << strerror(errno) << endl;
        close(CONN);
        return 1;
    }
    cout << "Client Received: " << string(buffer, mLen) << endl;
    close(CONN);
    return 0;
}
