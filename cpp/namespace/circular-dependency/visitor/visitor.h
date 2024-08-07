#ifndef _VISITOR_H_
#define _VISITOR_H_

class Element;

class Visitor {
public:
    void visit(Element *element);
};

#endif // _VISITOR_H_