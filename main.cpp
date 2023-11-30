
#include "include/Peers/provider.h"
#include "include/Peers/requester.h"
#include "include/Peers/bootstrap_node.h"
#include "include/utility.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    // const char* host = "";
    unsigned short port = 8080;
    // BootstrapNode bootstrap
    vector<int> trainingData{2, 1, 4, 3, 6, 5, 9, 7, 8, 10};

#if defined(PROVIDER)
    std::cout << "Running as provider on port " << port << "." << std::endl;
    Provider p = Provider(port);
    p.listen();
#elif defined(REQUESTER)
    std::cout << "Running as requester." << std::endl;
    Requester r = Requester(port);
    TaskRequest request = TaskRequest(trainingData);
    r.set_task_request(request);

    // sets the leaderIP and providerPeers
    r.send_discovery_request();

    // sends the task request to the leader and provider peers
    r.send_task_request();
    std::cout << "Sent task request." << std::endl;

#else
    std::cout << "Please specify either --provider or --requester flag."
              << std::endl;
#endif
}
