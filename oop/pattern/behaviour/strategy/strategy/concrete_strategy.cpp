#include "concrete_strategy.h"

ConcreteStrategyA::~ConcreteStrategyA() {

}

void ConcreteStrategyA::execute() {
    std::cout << "use strategy A" << std::endl;
    // ...
}

ConcreteStrategyB::~ConcreteStrategyB() {

}

void ConcreteStrategyB::execute() {
    std::cout << "use strategy B" << std::endl;
    // ...
}