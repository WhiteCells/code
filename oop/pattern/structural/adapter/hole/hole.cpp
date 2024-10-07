#include "hole.h"

Hole::Hole(double radius)
    : radius_(radius) {

}

bool Hole::isAccommodate(Round *round) {
    return radius_ >= round->getRadius();
}