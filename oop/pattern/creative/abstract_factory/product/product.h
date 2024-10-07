#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <string>

class ProductA {
public:
    ProductA() {}
    virtual ~ProductA() {}
    virtual std::string getProductInfo() = 0;
};

class ProductA1 : public ProductA {
public:
    ProductA1() {}
    ~ProductA1() {}
    virtual std::string getProductInfo() override;
};

class ProductA2 : public ProductA {
public:
    ProductA2() {}
    ~ProductA2() {}
    virtual std::string getProductInfo() override;
};

class ProductB {
public:
    ProductB() {}
    virtual ~ProductB() {}
    virtual std::string getProductInfo() = 0;
};


class ProductB1 : public ProductB {
public:
    ProductB1() {}
    ~ProductB1() {}
    virtual std::string getProductInfo() override;
};

class ProductB2 : public ProductB {
public:
    ProductB2() {}
    ~ProductB2() {}
    virtual std::string getProductInfo() override;
};

#endif // _PRODUCT_H_