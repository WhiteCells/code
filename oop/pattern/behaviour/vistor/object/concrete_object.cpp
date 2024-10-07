#include "concrete_object.h"
#include "visitor.h"

ConcreteObject::~ConcreteObject() {

}

void ConcreteObject::accept(Visitor *visitor) {
    visitor->visit(this);
}

void ConcreteObject::operate() {
    std::cout << "object operate" << std::endl;
}