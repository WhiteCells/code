#ifndef _STATE_B_H_
#define _STATE_B_H_

#include "state.h"
#include <iostream>

class StateB : public State
{
public:
    virtual void handle() override
    {
        std::cout << "StateB::handle" << std::endl;
    }
};

#endif // _STATE_B_H_