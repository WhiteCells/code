#include "pot.h"

Pot::Pot(double x, double y, PotType *type)
    : x_(x), y_(y), type_(type) {
    
}

void Pot::display() {
    type_->display(x_, y_);
}