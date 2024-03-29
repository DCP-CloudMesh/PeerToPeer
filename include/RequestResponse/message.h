#ifndef _MESSAGE_
#define _MESSAGE_

#include <string>
#include <memory>
#include "payload.h"
#include "../utility.h"

class Message {
    std::string uuid;
    std::string senderUuid;
    IpAddress senderIpAddr;
    std::shared_ptr<Payload> payload;

  public:
    Message();
    Message(const std::string& senderUuid, const IpAddress& senderIpAddr,
            std::shared_ptr<Payload> payload);
    virtual ~Message();

    std::string getUuid() const;
    std::string getSenderUuid() const;
    IpAddress getSenderIpAddr() const;
    std::shared_ptr<Payload> getPayload() const;
    void setPayload(std::shared_ptr<Payload> payload);
    void initializePayload(const std::string& payloadTypeStr);
    std::string serialize() const;
    void deserialize(const std::string& serializedData);
};

#endif // _MESSAGE_
