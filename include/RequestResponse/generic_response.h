#ifndef _GENERIC_RESPONSE_
#define _GENERIC_RESPONSE_

#include <string>
#include "payload.h"
#include "../utility.h"

class GenericResponse : public Payload {
  public:
    enum Status {
        FAILED,
        SUCCESS
    };

    GenericResponse();
    GenericResponse(const Status status);

    Status getStatus() const;
    std::string serialize() const override;
    void deserialize(const std::string& serializedData) override;
  
  protected:
    Status status;
};

#endif // _GENERIC_RESPONSE_
