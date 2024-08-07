#include "concrete_object.h"
#include "concrete_visitor.h"

int main(int argc, char *argv[]) {
    Visitor *visitor = new ConcreteVisitor();
    Object *object = new ConcreteObject();
    visitor->visit(object);

    delete visitor;
    delete object;
    return 0;
}