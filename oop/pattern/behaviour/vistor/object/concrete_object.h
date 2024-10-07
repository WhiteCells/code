#ifndef _CONCRETE_OBJECT_H_
#define _CONCRETE_OBJECT_H_

#include "object.h"
#include <iostream>

class Object;

class ConcreteObject : public Object {
public:
    virtual ~ConcreteObject() override;
    virtual void accept(Visitor *visitor) override;
    virtual void operate() override;
};

#endif // _CONCRETE_OBJECT_H_