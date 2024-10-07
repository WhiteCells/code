#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include "observer.h"

class Subject {
public:
    virtual ~Subject() {}
    virtual void attach(Observer *server) = 0;
    virtual void detach(Observer *server) = 0;
    virtual void notify() = 0;
};

#endif // _SUBJECT_H_