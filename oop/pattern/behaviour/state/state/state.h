#ifndef _STATE_H_
#define _STATE_H_

#include <iostream>

class State {
public:
    virtual void handle() = 0;
};

#endif // _STATE_H_