#include "pot_type.h"

PotType::PotType(std::string id, std::string color, double size)
    : id_(id), color_(color), size_(size) {
    
}

void PotType::display(double x, double y) {
    // std::cout << id_ << color_ << size_ << x << y << std::endl;
}