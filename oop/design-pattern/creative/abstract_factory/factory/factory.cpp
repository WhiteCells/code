#include "factory.h"

std::shared_ptr<ProductA> Factory1::createProductA() {
    return std::make_shared<ProductA1>();
}

std::shared_ptr<ProductB> Factory1::createProductB() {
    return std::make_shared<ProductB1>();
}

std::shared_ptr<ProductA> Factory2::createProductA() {
    return std::make_shared<ProductA2>();
}

std::shared_ptr<ProductB> Factory2::createProductB() {
    return std::make_shared<ProductB1>();
}