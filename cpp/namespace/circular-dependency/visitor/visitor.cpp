#include "visitor.h"
#include "element.h"

void Visitor::visit(Element *element) {
    element->display(this);
}