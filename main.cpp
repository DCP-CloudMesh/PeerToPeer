
#include <iostream>
// #includNetworking/u "Peers/provider.h"
#include "Peers/Provider/provider.h"
// #include "Peers/requester.h"
// #include "Networking/utility.cpp"
// #include "utility.h"

using namespace std;

int main(int argc, char* argv[]) {
    // cout << startNgrokForwarding(8181) << endl;

#if defined(PROVIDER)
    const char* host = "";
    const char* port = "8080";
    Provider p = Provider(host, port);
    std::cout << "Running as provider." << std::endl;
// Provider provider;
// provider.run();
#elif defined(REQUESTER)
    std::cout << "Running as requester." << std::endl;
// Requester requester;
// requester.run();
#else
    std::cout << "Please specify either --provider or --requester flag."
              << std::endl;
#endif
}
