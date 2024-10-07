#ifndef _CONCRETE_TEMPLATE_H_
#define _CONCRETE_TEMPLATE_H_

#include "template.h"
#include <iostream>

class ConcreteTemplate1 : public Template {
public:
    virtual ~ConcreteTemplate1() override {

    }
protected:
    virtual void operateA() override {
        std::cout << "template1 operate A" << std::endl;
    }

    virtual void operateB() override {
        std::cout << "template1 operate B" << std::endl;
    }
};

class ConcreteTemplate2 : public Template {
public:
    virtual ~ConcreteTemplate2() override {

    }

protected:
    virtual void operateA() override {
        std::cout << "template2 operate A" << std::endl;
    }

    virtual void operateB() override {
        std::cout << "template2 operate B" << std::endl;
    }
};

#endif // _CONCRETE_TEMPLATE_H_