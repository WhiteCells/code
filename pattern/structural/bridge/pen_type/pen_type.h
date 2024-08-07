#ifndef _PEN_TYPE_H_
#define _PEN_TYPE_H_

#include <string>

class PenType {
public:
    virtual std::string getPenType() = 0;
};

class BigPen : public PenType {
public:
    virtual std::string getPenType() override;
};

class SmallPen : public PenType {
public:
    virtual std::string getPenType() override;
};

#endif // _PEN_TYPE_H_