#ifndef _BUILDER_H_
#define _BUILDER_H_

#include "product.h"
#include <iostream>

class Builder {
public:
    Builder() {}
    ~Builder() {}

    Product getProduct() {
        return product_;
    }

    virtual void buildAttributeA() = 0;
    virtual void buildAttributeB() = 0;
    virtual void buildAttributeC() = 0;

protected:
    Product product_;
};

class Builder1 : public Builder {
public:
    Builder1() {}
    ~Builder1() {}

    virtual void buildAttributeA() override;
    virtual void buildAttributeB() override;
    virtual void buildAttributeC() override;
};

class Builder2 : public Builder {
public:
    Builder2() {}
    ~Builder2() {}

    virtual void buildAttributeA() override;
    virtual void buildAttributeB() override;
    virtual void buildAttributeC() override;
};

#endif // _BUILDER_H_