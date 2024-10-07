#include "builder.h"
#include "director.h"
#include "product.h"
#include <iostream>
#include <memory>

int main(int argc, char *argv[]) {
    Builder *builder;
    Director *director = new Director();
    Product product;

    builder = new Builder1();
    director->setBuilder(builder);
    product = director->constructProduct();

    builder = new Builder2();
    director->setBuilder(builder);
    product = director->constructProduct();

    delete builder;
    delete director;
    
    return 0;
}