#ifndef _DISCOVERY_RESPONSE_
#define _DISCOVERY_RESPONSE_

#include <string>
#include "payload.h"
#include "../utility.h"

class DiscoveryResponse : public Payload {
    AddressTable availablePeers; 
  public:
    DiscoveryResponse();
    DiscoveryResponse(const AddressTable& availablePeers);

    AddressTable getAvailablePeers() const;
    std::string serialize() const override;
    void deserialize(const std::string& serializedData) override;
};

#endif // _DISCOVERY_RESPONSE_
