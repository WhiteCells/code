#include "builder.h"

void Builder1::buildAttributeA() {
    product_.setAttributeA("Builder1 A");
    std::cout << "product builder1 A" << std::endl;
}

void Builder1::buildAttributeB() {
    product_.setAttributeB("Builder1 B");
    std::cout << "product builder1 B" << std::endl;
}

void Builder1::buildAttributeC() {
    product_.setAttributeC("Builder1 C");
    std::cout << "product builder1 C" << std::endl;
}

void Builder2::buildAttributeA() {
    product_.setAttributeA("Builder2 A");
    std::cout << "product builder2 A" << std::endl;
}

void Builder2::buildAttributeB() {
    product_.setAttributeB("Builder2 B");
    std::cout << "product builder2 B" << std::endl;
}

void Builder2::buildAttributeC() {
    product_.setAttributeC("Builder2 C");
    std::cout << "product builder2 C" << std::endl;
}