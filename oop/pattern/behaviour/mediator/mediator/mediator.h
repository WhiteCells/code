#ifndef _MEDIATOR_H_
#define _MEDIATOR_H_

#include "user.h"

class User;

class Mediator {
public:
    virtual ~Mediator() = 0;
    virtual void registerUser(User *user) = 0;
    virtual void operate(User *user) = 0;
};

#endif // _MEDIATOR_H_