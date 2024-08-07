#ifndef _OBJECT_H_
#define _OBJECT_H_

class Visitor;

class Object {
public:
    virtual ~Object();
    virtual void accept(Visitor *visitor) = 0;
    virtual void operate() = 0;
};

#endif // _OBJECT_H_