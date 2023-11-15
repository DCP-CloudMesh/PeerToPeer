#include "provider.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

string Provider::getPublicIPAddr() {
    const char* command = "python3 ngrok.py";

    // Open a pipe to capture the output
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        std::cerr << "Error opening pipe." << std::endl;
        return EXIT_FAILURE;
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

    // Print the captured output
    std::cout << "Python script output:\n" << result << std::endl;

    return result;
}
