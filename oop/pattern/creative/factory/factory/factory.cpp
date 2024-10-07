#include "factory.h"

std::shared_ptr<Product> FactoryA::createProduct() {
    return std::make_shared<ProductA>();
}

std::shared_ptr<Product> FactoryB::createProduct() {
    return std::make_shared<ProductB>();
}