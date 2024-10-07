#ifndef _CONCRETE_VISITOR_H_
#define _CONCRETE_VISITOR_H_

#include "visitor.h"

class ConcreteVisitor : public Visitor {
public:
    virtual ~ConcreteVisitor() override;
    virtual void visit(Object *object) override;
};

#endif // _CONCRETE_VISITOR_H_