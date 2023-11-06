
#include <iostream>
// #include "Peers/provider.h"
// #include "Peers/requester.h"

int main(int argc, char* argv[]) {

    #if defined( PROVIDER )
    std::cout << "Running as provider." << std::endl;
    // Provider provider;
    // provider.run();
    #elif defined( REQUESTER )
    std::cout << "Running as requester." << std::endl;
    // Requester requester;
    // requester.run();
    #else
    std::cout << "Please specify either --provider or --requester flag." << std::endl;
    #endif

}
