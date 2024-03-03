#include "../../include/RequestResponse/generic_response.h"

using namespace std;
using namespace nlohmann;

GenericResponse::GenericResponse()
    : Payload(Type::GENERIC_RESPONSE), status{SUCCESS} {}


GenericResponse::GenericResponse(const GenericResponse::Status status)
    : Payload(Type::GENERIC_RESPONSE), status{status} {}

GenericResponse::Status GenericResponse::getStatus() const { return status; }

string GenericResponse::serialize() const {
    json j;
    j["status"] = status;
    return j.dump();
}

void GenericResponse::deserialize(const string& serializedData) {
    try {
        json j = json::parse(serializedData);
        status = j["status"].get<Status>();
    } catch (json::exception& e) {
        cout << "JSON parsing error: " << e.what() << endl;
    }
}
