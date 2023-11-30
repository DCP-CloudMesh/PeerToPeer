#include "../../include/Networking/server.h"

using namespace std;

Server::Server(const char* host, const char* port, const char* type)
    : HOST{host}, PORT{port}, TYPE{type}, server{-1} {}

void Server::setupServer() {
    std::string response = startNgrokForwarding(stoi(PORT));

    // update public IP address
    response = response.substr(6);
    std::string ip =
        response.substr(0, response.find(":")); // ignore "tcp://" prefix
    unsigned short port = std::stoi(response.substr(ip.length() + 1));
    publicIP = IpAddress{ip, port};

    cout << "Server Running on " << ip << ". Port: " << port << endl;

    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == -1) {
        cerr << "Error creating socket: " << strerror(errno) << endl;
        exit(1);
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(stoi(PORT));
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (::bind(server, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) ==
        -1) {
        cerr << "Error binding: " << strerror(errno) << endl;
        close(server);
        exit(1);
    }

    if (listen(server, 5) == -1) {
        cerr << "Error listening: " << strerror(errno) << endl;
        close(server);
        exit(1);
    }

    cout << "Waiting for client..." << endl;
}

void Server::acceptConn() {
    while (true) {
        sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        int connection =
            accept(server, (struct sockaddr*)&clientAddr, &clientAddrLen);

        if (connection == -1) {
            cerr << "Error accepting: " << strerror(errno) << endl;
            close(server);
            exit(1);
        }

        cout << "Client connected" << endl;
        processClient(connection);
    }
}

void Server::processClient(int connection) {
    char buffer[1024];
    ssize_t mLen = recv(connection, buffer, sizeof(buffer), 0);
    if (mLen < 0) {
        cerr << "Error reading: " << strerror(errno) << endl;
    }
    cout << "Received: " << string(buffer, mLen) << endl;

    const char* response = "Thanks! Got your message:";
    send(connection, response, strlen(response), 0);
    send(connection, buffer, mLen, 0);

    close(connection);
}
