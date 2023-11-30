
#include "include/Peers/provider.h"
#include "include/Peers/requester.h"
#include "include/utility.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    // const char* host = "";
    const char* port = "8080";

#if defined(PROVIDER)
    std::cout << "Running as provider." << std::endl;
    Provider p = Provider(atoi(port));
    p.listen();
#elif defined(REQUESTER)
    std::cout << "Running as requester." << std::endl;
    Requester r = Requester();
    r.set_task_request(TaskRequest("test", unordered_set<string>({"test"})));
    r.send_discovery_request();
    r.send_task_request();
    std::cout << "Sent task request." << std::endl;
#else
    std::cout << "Please specify either --provider or --requester flag."
              << std::endl;
#endif
}
