#ifndef _ORIGINATOR_H_
#define _ORIGINATOR_H_

#include "memento.h"

class Originator {
public:
    Originator(std::string state);
    void setState(const std::string &state);
    std::string getState() const;
    Memento createMemento();
    void restoreFromMemento(const Memento &memento);

private:
    std::string state_;
};

#endif // _ORIGINATOR_H_