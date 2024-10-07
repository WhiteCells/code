#ifndef _CARETAKER_H_
#define _CARETAKER_H_

#include "memento.h"
#include <vector>

class Caretaker {
public:
    void addMemento(const Memento &memento);
    Memento getMemento(int index) const;

private:
    std::vector<Memento> mementos_;
};

#endif // _CARETAKER_H_