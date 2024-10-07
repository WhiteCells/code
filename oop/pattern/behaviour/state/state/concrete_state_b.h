#ifndef _CONCRETE_STATE_B_H_
#define _CONCRETE_STATE_B_H_

#include "state.h"

class ConcreteStateB : public State {
public:
    virtual void handle() override {
        std::cout << "process of state B" << std::endl;
    }
};

#endif // _CONCRETE_STATE_B_H_