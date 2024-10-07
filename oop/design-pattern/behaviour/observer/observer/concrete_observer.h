#ifndef _CONCRETE_OBSERVER_H_
#define _CONCRETE_OBSERVER_H_

#include "observer.h"
#include <iostream>

class ConcreteObserver : public Observer {
public:
    virtual void update() override {
        std::cout << "observer recevice update" << std::endl;
    }
};

#endif // _CONCRETE_OBSERVER_H_