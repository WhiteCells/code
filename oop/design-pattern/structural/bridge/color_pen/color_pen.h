#ifndef _COLOR_PEN_H_
#define _COLOR_PEN_H_

#include "pen_type.h"
#include <string>
#include <iostream>

class ColorPen {
public:
    ColorPen(PenType *type) : pen_type(type) {}
    virtual void write(std::string text) = 0;

protected:
    PenType *pen_type;
};

class RedPen : public ColorPen {
public:
    RedPen(PenType *type) : ColorPen(type) {}
    virtual void write(std::string text) override;
};

class BluePen : public ColorPen {
public:
    BluePen(PenType *type) : ColorPen(type) {}
    virtual void write(std::string text) override;
};

#endif // _COLOR_PEN_H_