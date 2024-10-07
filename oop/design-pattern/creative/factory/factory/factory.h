#ifndef _FACTOR_H_
#define _FACTOR_H_

#include "product.h"
#include <memory>

class Factory {
public:
    Factory() {}
    virtual ~Factory() {}
    virtual std::shared_ptr<Product> createProduct() = 0;
};

class FactoryA : public Factory {
public:
    FactoryA() {}
    ~FactoryA() {}
    virtual std::shared_ptr<Product> createProduct() override;
};

class FactoryB : public Factory {
public:
    FactoryB() {}
    ~FactoryB() {}
    virtual std::shared_ptr<Product> createProduct() override;
};

#endif // _FACTOR_H_