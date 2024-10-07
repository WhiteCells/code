#include "round_adapter.h"

RoundAdapter::RoundAdapter(Square *square) : square_(square) {

}

double RoundAdapter::getRadius() const {
    return square_->getLength() * std::sqrt(2) / 2;
}