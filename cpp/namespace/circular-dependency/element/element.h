#ifndef _ELEMENT_H_
#define _ELEMENT_H_

class Visitor;

class Element {
public:
    explicit Element(int val);
    void display(Visitor *visitor);

private:
    int val_;
};

#endif // _ELEMENT_H_