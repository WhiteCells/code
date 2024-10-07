#ifndef _SQUARE_ADAPTER_H_
#define _SQUARE_ADAPTER_H_

#include "round.h"
#include "square.h"
#include <cmath>

class RoundAdapter : public Round {
public:
    RoundAdapter(Square *square);
    ~RoundAdapter() {}

    double getRadius() const;

private:
    Square *square_;
};

#endif // _SQUARE_ADAPTER_H_