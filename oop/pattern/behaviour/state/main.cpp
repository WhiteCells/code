#include "concrete_state_a.h"
#include "concrete_state_b.h"
#include "context.h"

int main(int argc, char *argv[]) {
    Context *context = new Context();

    context->setState(new ConcreteStateA());
    context->request();

    context->setState(new ConcreteStateB());
    context->request();

    delete context;
    context = nullptr;

    return 0;
}