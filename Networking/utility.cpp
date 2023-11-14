#include <sstream>
#include <iostream>

std::string getPublicIPAddr() {
    const char* command = "python3 ./Peers/ngrok-ip.py";

    // Open a pipe to capture the output
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        std::cerr << "Error opening pipe." << std::endl;
        return "";
    }

    // Read the output of the Python script
    char buffer[256];
    std::string result = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 256, pipe) != nullptr)
            result += buffer;
    }

    // Close the pipe
    pclose(pipe);
    return result;
}
