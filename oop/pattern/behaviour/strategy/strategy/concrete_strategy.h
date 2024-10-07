#ifndef _CONCRETE_STRATEGY_H_
#define _CONCRETE_STRATEGY_H_

#include "strategy.h"
#include <iostream>

class ConcreteStrategyA : public Strategy {
public:
    virtual ~ConcreteStrategyA() override;
    virtual void execute() override;
};

class ConcreteStrategyB : public Strategy {
public:
    virtual ~ConcreteStrategyB() override;
    virtual void execute() override;
};

#endif // _CONCRETE_STRATEGY_H_