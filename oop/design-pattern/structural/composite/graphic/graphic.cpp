#include "graphic.h"

Graphic::~Graphic() {
    std::cout << "~Graphic" << std::endl;
}

Dot::Dot(double x, double y) : x_(x), y_(y) {

}

void Dot::move(double x, double y) {
    x_ += x;
    y_ += y;
}

void Dot::draw() {
    std::cout <<
        "draw dot (" << x_ << ", " << y_ << ")"
        << std::endl;
}

Circle::Circle(double x, double y, double radius)
    : x_(x), y_(y), radius_(radius) {

}

void Circle::move(double x, double y) {
    x_ += x;
    y_ += y;
    radius_ += sqrt(x * x + y * y);
}

void Circle::draw() {
    std::cout <<
        "draw Circle ("
        << x_ << ", " << y_ << ", " << radius_ << ")"
        << std::endl;
}