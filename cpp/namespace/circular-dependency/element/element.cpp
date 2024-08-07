#include "element.h"
#include "visitor.h"
#include <iostream>

Element::Element(int val) : val_(val) {

}

void Element::display(Visitor *visitor) {
    std::cout << val_ << std::endl;
}