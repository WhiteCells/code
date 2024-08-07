#include "factory.h"
#include <iostream>

int main(int argc, char *argv[]) {
    std::shared_ptr<Product> product;
    std::shared_ptr<Factory> factory;

    // FactoryA
    factory = std::make_shared<FactoryA>();
    product = factory->createProduct();
    std::cout << product->getProductInfo() << std::endl;

    // FactoryB
    factory = std::make_shared<FactoryB>();
    product = factory->createProduct();
    std::cout << product->getProductInfo() << std::endl;
    return 0;
}