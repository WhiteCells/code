#ifndef _DIRECTOR_H_
#define _DIRECTOR_H_

#include "builder.h"

class Director {
public:
    Director() : builder_(nullptr) {}
    ~Director() {
        if (builder_) {
            delete builder_;
        }
    }

    void setBuilder(Builder *builder);

    Product constructProduct();

private:
    Builder *builder_;
};

#endif // _DIRECTOR_H_