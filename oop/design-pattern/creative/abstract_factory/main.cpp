#include "factory.h"
#include "product.h"
#include <iostream>

int main(int argc, char *argv[]) {
    std::shared_ptr<Factory> factory;
    std::shared_ptr<ProductA> product_a;
    std::shared_ptr<ProductB> product_b;

    factory = std::make_shared<Factory1>();
    product_a = factory->createProductA();
    product_b = factory->createProductB();
    std::cout << product_a->getProductInfo() << std::endl;
    std::cout << product_b->getProductInfo() << std::endl;

    factory = std::make_shared<Factory2>();
    product_a = factory->createProductA();
    product_b = factory->createProductB();
    std::cout << product_a->getProductInfo() << std::endl;
    std::cout << product_b->getProductInfo() << std::endl;
    return 0;
}