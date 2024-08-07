#ifndef _CONCRETE_STATE_A_H_
#define _CONCRETE_STATE_A_H_

#include "state.h"

class ConcreteStateA : public State {
public:
    virtual void handle() override {
        std::cout << "process of state A" << std::endl;
    }
};

#endif // _CONCRETE_STATE_A_H_