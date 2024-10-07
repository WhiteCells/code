#ifndef _FACTORY_H_
#define _FACTORY_H_

#include "product.h"
#include <memory>

class Factory {
public:
    Factory() {}
    virtual ~Factory() {}
    virtual std::shared_ptr<ProductA> createProductA() = 0;
    virtual std::shared_ptr<ProductB> createProductB() = 0;
};

class Factory1 : public Factory {
public:
    Factory1() {}
    ~Factory1() {}
    virtual std::shared_ptr<ProductA> createProductA() override;
    virtual std::shared_ptr<ProductB> createProductB() override;
};

class Factory2 : public Factory {
public:
    Factory2() {}
    ~Factory2() {}
    virtual std::shared_ptr<ProductA> createProductA() override;
    virtual std::shared_ptr<ProductB> createProductB() override;
};

#endif // _FACTORY_H_