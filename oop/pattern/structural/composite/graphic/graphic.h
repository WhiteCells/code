#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#include <iostream>
#include <cmath>

class Graphic {
public:
    virtual ~Graphic() = 0;
    virtual void move(double x, double y) = 0;
    virtual void draw() = 0;
};

class Dot : public Graphic {
public:
    Dot(double x = 0, double y = 0);
    virtual void move(double x, double y) override;
    virtual void draw() override;

private:
    double x_;
    double y_;
};

class Circle : public Graphic {
public:
    Circle(double x = 0, double y = 0, double radius = 0);

    virtual void move(double x, double y) override;
    virtual void draw() override;

private:
    double x_;
    double y_;
    double radius_;
};

#endif // _GRAPHIC_H_