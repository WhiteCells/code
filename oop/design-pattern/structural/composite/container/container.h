#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include "graphic.h"
#include <map>

class Container : public Graphic {
public:
    virtual ~Container();

    virtual void move(double x, double y) override;
    virtual void draw() override;

    bool add(int id, Graphic *graphic);
    bool remove(int id);

private:
    std::map<int, Graphic *> children_;
};

#endif // _CONTAINER_H_