#include "color_pen.h"

void RedPen::write(std::string text) {
    std::cout << "red " << pen_type->getPenType() << " -> "
        << text << std::endl;
}

void BluePen::write(std::string text) {
    std::cout << "blue " << pen_type->getPenType() << " -> "
        << text << std::endl;
}