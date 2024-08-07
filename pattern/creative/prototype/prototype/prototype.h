#ifndef _PROTOTYPE_H_
#define _PROTOTYPE_H_

class Prototype {
public:
    virtual Prototype *clone() = 0;
};

#endif // _PROTOTYPE_H_