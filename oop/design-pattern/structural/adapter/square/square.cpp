#include "square.h"

Square::Square(double length)
    : length_(length) {
    
}

double Square::getLength() const {
    return this->length_;
}