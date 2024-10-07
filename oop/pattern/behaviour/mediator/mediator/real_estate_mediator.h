#ifndef _REAL_ESTATE_MEDIATOR_H_
#define _REAL_ESTATE_MEDIATOR_H_

#include "mediator.h"
#include <vector>

class RealEstateMediator : public Mediator {
public:
    virtual ~RealEstateMediator() override;
    void registerUser(User *user);
    void operate(User *ask_user);

private:
    std::vector<User *> user_list_;
};

#endif // _REAL_ESTATE_MEDIATOR_H_