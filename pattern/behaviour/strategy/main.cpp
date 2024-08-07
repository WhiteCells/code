#include "context.h"
#include "concrete_strategy.h"

int main(int argc, char *argv[]) {
    Context *context = new Context(new ConcreteStrategyA());
    context->process();

    context->setStrategy(new ConcreteStrategyB());
    context->process();

    delete context;
    return 0;
}