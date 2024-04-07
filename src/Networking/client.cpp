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
        cerr << "Error getting address info: " << gai_strerror(errno) << endl;
        return 1;
    }

    for (auto addr = serverInfo; addr != nullptr; addr = addr->ai_next) {
        CONN = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (CONN == -1) {
            cerr << "Error creating socket: " << strerror(errno) << endl;
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

int Client::sendRequest(const char* data) {
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

    // FTP (draft)
    char *token, *dummy;
    dummy = buffer;
    token = strtok(dummy, " ");
    // process file descriptor
    if (strcmp("get", token) == 0) {
        char port[MAXLINE], buffer[MAXLINE], char_num_blks[MAXLINE],
            char_num_last_blk[MAXLINE];
        int datasock, lSize, num_blks, num_last_blk, i;
        FILE* fp;
        token = strtok(NULL, " \n");
        cout << "Filename given is: " << token << endl;
        int data_port = 1024;
        sprintf(port, "%d", data_port);
        datasock =
            FTP_create_socket_server(data_port);     // creating socket for data connection
        send(CONN, port, MAXLINE, 0);   // sending port no. to client
        datasock = FTP_accept_conn(datasock); // accepting connnection by client
        if ((fp = fopen(token, "r")) != NULL) {
            // size of file
            send(CONN, "nxt", MAXLINE, 0);
            fseek(fp, 0, SEEK_END);
            lSize = ftell(fp);
            rewind(fp);
            num_blks = lSize / MAXLINE;
            num_last_blk = lSize % MAXLINE;
            sprintf(char_num_blks, "%d", num_blks);
            send(CONN, char_num_blks, MAXLINE, 0);
            // cout<<num_blks<<"	"<<num_last_blk<<endl;

            for (i = 0; i < num_blks; i++) {
                fread(buffer, sizeof(char), MAXLINE, fp);
                send(datasock, buffer, MAXLINE, 0);
                // cout<<buffer<<"	"<<i<<endl;
            }
            sprintf(char_num_last_blk, "%d", num_last_blk);
            send(CONN, char_num_last_blk, MAXLINE, 0);
            if (num_last_blk > 0) {
                fread(buffer, sizeof(char), num_last_blk, fp);
                send(datasock, buffer, MAXLINE, 0);
                // cout<<buffer<<endl;
            }
            fclose(fp);
            cout << "File upload done.\n";
        } else {
            send(CONN, "0", MAXLINE, 0);
        }
    }

    close(CONN);
    return 0;
}
