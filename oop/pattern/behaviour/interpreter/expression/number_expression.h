#ifndef _NUMBER_EXPRESSION_H_
#define _NUMBER_EXPRESSION_H_

#include "expression.h"

class NumberExpression : public Expression {
public:
    NumberExpression(int val) : val_(val) {}
    virtual int interpreter() override {
        return val_;
    }

private:
    int val_;
};

#endif // _NUMBER_EXPRESSION_H_