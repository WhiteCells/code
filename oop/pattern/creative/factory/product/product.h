#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <string>

class Product {
public:
    Product() {}
    virtual ~Product() {}
    virtual std::string getProductInfo() = 0;
};

class ProductA : public Product {
public:
    ProductA() {}
    ~ProductA() {}
    virtual std::string getProductInfo() override;
};

class ProductB : public Product {
public:
    ProductB() {}
    ~ProductB() {}
    virtual std::string getProductInfo() override;
};

#endif // _PRODUCT_H_