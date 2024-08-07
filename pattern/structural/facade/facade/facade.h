#ifndef _FACADE_H_
#define _FACADE_H_

#include "system.h"

class Facade {
public:
    Facade();
    ~Facade();
    void wrapSystemOperate();

private:
    SystemA *system_a_;
    SystemB *system_b_;
    SystemC *system_c_;
};

#endif // _FACADE_H_