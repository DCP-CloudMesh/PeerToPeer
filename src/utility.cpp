#include "../include/utility.h"

using namespace std;

std::string serializeIpAddress(const IpAddress& ipAddress) {
    json j;
    j["ip"] = ipAddress.ipAddress;
    j["port"] = ipAddress.port;
    return j.dump();
}

IpAddress deserializeIpAddress(const std::string& jsonString) {
    IpAddress ipAddress;
    try {
        json j = json::parse(jsonString);
        ipAddress.ipAddress = j["ip"].get<std::string>();
        ipAddress.port = j["port"].get<unsigned short>();
    } catch (json::exception& e) {
        std::cout << "JSON parsing error for IpAddress: " << e.what()
                  << std::endl;
    }
    return ipAddress;
}

string uuid::generate_uuid_v4() {
    stringstream ss;
    int i;
    ss << hex;
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

string startNgrokForwarding(unsigned short port) {
    const string command =
        "python3 ./src/Networking/ngrok_ip.py " + to_string(port);

    // start ngrok
    string ngrok_restart =
        "./src/Networking/ngrok_restart.sh " + to_string(port) + " &";
    system(ngrok_restart.c_str());

    // Open a pipe to capture the output
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        cerr << "Error opening pipe." << endl;
        return "";
    }

    // read
    char buffer[256];
    string result = "";
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

void close_ngrok_forwarding() { system("pkill ngrok"); }

string vectorToString(vector<int> vec) {
    stringstream ss;
    for (unsigned int i = 0; i < vec.size(); i++) {
        ss << vec[i];
        if (i != vec.size() - 1) {
            ss << ",";
        }
    }

    return ss.str();
}
