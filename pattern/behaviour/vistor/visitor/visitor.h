#ifndef _VISITOR_H_
#define _VISITOR_H_

class Object;

class Visitor {
public:
    virtual ~Visitor();
    virtual void visit(Object *object) = 0;
};

#endif // _VISITOR_H_