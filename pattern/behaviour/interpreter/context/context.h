#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "expression.h"
#include <stack>

class Context {
public:
    void pushExpression(Expression *expression) {
        expression_stack_.push(expression);
    }

    Expression *popExpression() {
        if (!expression_stack_.empty()) {
            Expression *expression = expression_stack_.top();
            expression_stack_.pop();
            return expression;
        }
        return nullptr;
    }

private:
    std::stack<Expression *> expression_stack_;
};

#endif // _CONTEXT_H_