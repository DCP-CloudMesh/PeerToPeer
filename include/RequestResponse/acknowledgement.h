#ifndef _ACKNOWLEDGEMENT_
#define _ACKNOWLEDGEMENT_

#include <string>
#include "payload.h"
#include "../utility.h"

class Acknowledgement : public Payload {
  public:
    Acknowledgement();

    std::string serialize() const override;
    void deserialize(const std::string& serializedData) override;
};

#endif // _ACKNOWLEDGEMENT_
