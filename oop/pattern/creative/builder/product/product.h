#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <string>
#include <iostream>

class Product {
public:
    Product() {}
    virtual ~Product() {}

    void setAttributeA(std::string a);
    void setAttributeB(std::string b);
    void setAttributeC(std::string c);

private:
    std::string attribute_a_;
    std::string attribute_b_;
    std::string attribute_c_;
};

#endif // _PRODUCT_H_