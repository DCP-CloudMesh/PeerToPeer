#include "../include/utility.h"

std::string uuid::generate_uuid_v4() {
    std::stringstream ss;
    int i;
    ss << std::hex;
    for (i = 0; i < 8; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 4; i++) {
        ss << dis(gen);
    }
    ss << "-4";
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    ss << dis2(gen);
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 12; i++) {
        ss << dis(gen);
    };
    return ss.str();
}

std::string startNgrokForwarding(unsigned short port) {
    const std::string command =
        "python3 ./src/Networking/ngrok_ip.py " + std::to_string(port);

    // start ngrok
    std::system("./src/Networking/ngrok_restart.sh 8181 &");

    // Open a pipe to capture the output
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Error opening pipe." << std::endl;
        return "";
    }

    // read
    char buffer[256];
    std::string result = "";
    // while (fgets(buffer, 256, pipe) != nullptr) {
    //     result += buffer;
    // }

    // // Close the pipe
    // pclose(pipe);
    // return result;
    while (!feof(pipe)) {
        if (fgets(buffer, 256, pipe) != nullptr)
            result += buffer;
    }

    // Close the pipe
    pclose(pipe);
    return result;
}

void close_ngrok_forwarding() { std::system("pkill ngrok"); }
