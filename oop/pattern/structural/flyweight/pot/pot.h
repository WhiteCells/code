#ifndef _POT_TYPE_H_
#define _POT_TYPE_H_

#include "pot_type.h"

class Pot {
public:
    Pot(double x, double y, PotType *type);
    void display();

private:
    PotType *type_;
    double x_;
    double y_;
};

#endif // _POT_TYPE_H_