#ifndef _OBSERVER_B_H_
#define _OBSERVER_B_H_

#include "observer.h"
#include <iostream>

class ObserverB : public Observer
{
public:
    virtual void update()
    {
        std::cout << "ObserverB::update" << std::endl;
    }
};

#endif // _OBSERVER_B_H_