#ifndef _OBSERVER_A_H_
#define _OBSERVER_A_H_

#include "observer.h"
#include <iostream>

class ObserverA : public Observer
{
public:
    virtual void update()
    {
        std::cout << "ObserverA::update" << std::endl;
    }
};

#endif // _OBSERVER_A_H_