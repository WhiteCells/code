#ifndef _HOLE_H_
#define _HOLE_H_

#include "round.h"
#include "square.h"

class Hole {
public:
    Hole(double radius);

    bool isAccommodate(Round *round);

private:
    double radius_;
};

#endif // _HOLE_H_