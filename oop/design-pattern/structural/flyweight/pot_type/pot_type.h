#ifndef _POT_H_
#define _POT_H_

#include <string>
#include <iostream>

class PotType {
public:
    PotType(std::string id, std::string color, double size);
    void display(double x, double y);

private:
    std::string id_;
    std::string color_;
    double size_;
};

#endif // _POT_H_