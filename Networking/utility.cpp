#include <iostream>
#include <sstream>

std::string startNgrokForwarding(unsigned int port) {
    const std::string command = "python3 ngrok_ip.py " + std::to_string(port);

    // start ngrok
    std::system("./ngrok_restart.sh &");

    // Open a pipe to capture the output
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Error opening pipe." << std::endl;
        return "";
    }

    // read
    char buffer[256];
    std::string result = "";
    while (fgets(buffer, 256, pipe) != nullptr) {
        result += buffer;
    }

    // Close the pipe
    pclose(pipe);
    return result;
    while (!feof(pipe)) {
        if (fgets(buffer, 256, pipe) != nullptr)
            result += buffer;
    }

    // Close the pipe
    pclose(pipe);
    return result;
}
