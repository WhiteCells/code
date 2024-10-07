#ifndef _NORMAL_POT_H_
#define _NORMAL_POT_H_

#include <string>

class NormalPot {
public:
    NormalPot(std::string id, std::string color, double size, double x, double y);
    void display();

private:
    std::string id_;
    std::string color_;
    double size_;
    double x_;
    double y_;
};

#endif // _NORMAL_POT_H_