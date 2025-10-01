#ifndef _STATE_A_H_
#define _STATE_A_H_

#include "state.h"
#include <iostream>

class StateA : public State
{
public:
    virtual void handle() override
    {
        std::cout << "StateA::handle" << std::endl;
    }
};

#endif // _STATE_A_H_