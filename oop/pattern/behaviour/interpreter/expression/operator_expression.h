#ifndef _OPERATOR_EXPRESSION_H_
#define _OPERATOR_EXPRESSION_H_

#include "expression.h"
#include <iostream>

class OperatorExpression : public Expression {
public:
    OperatorExpression(Expression *left, Expression *right, char oper)
        : left_(left), right_(right), oper_(oper) {}
    virtual ~OperatorExpression() {
        if (left_) {
            delete left_;
            left_ = nullptr;
        }
        if (right_) {
            delete right_;
            right_ = nullptr;
        }
    }
    virtual int interpreter() override {
        switch (oper_) {
            case '+':
                return left_->interpreter() + right_->interpreter();
            case '-':
                return left_->interpreter() - right_->interpreter();
            case '*':
                return left_->interpreter() * right_->interpreter();
            case '/':
                if (right_->interpreter() == 0) {
                    std::cout << " 0 " << std::endl;
                }
                return left_->interpreter() / right_->interpreter();
            default:
                return 0;
        }
    }
private:
    Expression *left_;
    Expression *right_;
    char oper_;
};

#endif // _OPERATOR_EXPRESSION_H_