#ifndef _TENANT_H_
#define _TENANT_H_

#include "user.h"

class Tenant : public User {
public:
    Tenant(std::string name, std::string address,
           std::string phone, double price, Mediator *mediator);
    virtual ~Tenant() override;
    virtual void ask() override;
    virtual void answer() override;
};

#endif // _TENANT_H_