#include "../../include/RequestResponse/task_response.h"
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;

vector<int> TaskResponse::getTrainingData() const { return trainingData; }

std::string TaskResponse::serialize() const {
    json j;
    j["trainingData"] = trainingData;
    return j.dump();
}

void TaskResponse::deserialize(std::string msg) {
    try {
        json j = json::parse(msg);
        if (j.contains("trainingData"))
            trainingData = j["trainingData"].get<std::vector<int>>();

    } catch (json::exception& e) {
        cout << "JSON parsing error: " << e.what() << endl;
    }
}
