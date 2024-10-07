#ifndef _USER_H_
#define _USER_H_

#include "mediator.h"
#include <string>
#include <iostream>

class Mediator;

enum USER_TYPE {
    TENANT,
    LANDLORD,
};

class User {
public:
    User(std::string name, std::string address,
         std::string phone, double price,
         USER_TYPE type, Mediator *mediator);
    virtual ~User() = 0;
    virtual void ask() = 0;
    virtual void answer() = 0;
    void setMediator(Mediator *mediator);
    Mediator *getMediator() const;
    void setPersonType(USER_TYPE type);
    USER_TYPE getUserType() const;
    double getPrice() const;

protected:
    USER_TYPE type_;
    Mediator *mediator_;
    std::string name_;
    std::string address_;
    std::string phone_;
    double price_;
};

#endif // _USER_H_