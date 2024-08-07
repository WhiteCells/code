#include "visitor.h"
#include "element.h"

int main(int argc, char *argv[]) {
    Visitor *visitor = new Visitor();
    Element *element = new Element(10);
    visitor->visit(element);

    delete visitor;
    visitor = nullptr;

    delete element;
    element = nullptr;
    return 0;
}