#ifndef _REGISTRATION_
#define _REGISTRATION_

#include <string>
#include "payload.h"

class Registration : public Payload {
  public:
    Registration();

    std::string serialize() const override;
    void deserialize(const std::string& serializedData) override;
};

#endif // _REGISTRATION_
