#ifndef _LANDLORD_H_
#define _LANDLORD_H_

#include "user.h"

class Landlord : public User {
public:
    Landlord(std::string name, std::string address,
             std::string phone, double price, Mediator *mediator);
    virtual ~Landlord() override;
    virtual void ask() override;
    virtual void answer() override;
};

#endif // _LANDLORD_H_