#include "../../include/Networking/server.h"

using namespace std;

Server::Server(const char* host, const char* port, const char* type)
    : HOST{host}, PORT{port}, CONNTYPE{type}, server{-1} {}

void Server::setupServer() {
#if defined(NOLOCAL)
    string response = startNgrokForwarding(stoi(PORT));
    // update public IP address
    response = response.substr(6);
    std::string ip =
        response.substr(0, response.find(":")); // ignore "tcp://" prefix
    unsigned short port = static_cast<unsigned short>(
        std::stoi(response.substr(ip.length() + 1)));
    publicIP = IpAddress{ip, port};
#elif defined(LOCAL)
    publicIP = IpAddress{HOST, static_cast<unsigned short>(std::stoi(PORT))};
#else
    std::cerr << "Please specify either --local or --nolocal flag."
              << std::endl;
    exit(1);
#endif

    cout << "Initializing server on " << publicIP.ipAddress << ":"
         << publicIP.port << endl;

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

    cout << "Server initialized" << endl;
}

bool Server::acceptConn() {
    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    cout << "Waiting for client to connect..." << endl;
    activeConn = accept(server, (struct sockaddr*)&clientAddr, &clientAddrLen);

    if (activeConn == -1) {
        cerr << "Error accepting: " << strerror(errno) << endl;
        close(server);
        return false;
    }

    cout << "Client connected" << endl;
    return true;
}

string Server::receiveFromConn() {
    char buffer[1024];
    ssize_t mLen = recv(activeConn, buffer, sizeof(buffer), 0);
    if (mLen < 0) {
        cerr << "Error reading: " << strerror(errno) << endl;
    }
    cout << "Server Received: " << string(buffer, mLen) << endl;
    return string(buffer, mLen);
}

void Server::replyToConn(string message) {
    const char* reply = message.c_str();
    send(activeConn, reply, strlen(reply), 0);
}

void Server::closeConn() { close(activeConn); }

Server::~Server() {
    cout << "Closing server" << endl;
    if (server != -1) {
        close(server);
    }
}
