#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

class Expression {
public:
    virtual int interpreter() = 0;
    virtual ~Expression() {}
};

#endif // _EXPRESSION_H_