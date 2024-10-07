#include "concrete_object.h"
#include "concrete_visitor.h"

ConcreteVisitor::~ConcreteVisitor() {

}

void ConcreteVisitor::visit(Object *object) {
    if (Object *obj = dynamic_cast<ConcreteObject *>(object)) {
        obj->operate();
    }
}