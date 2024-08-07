#include "caretaker.h"

void Caretaker::addMemento(const Memento &memento) {
    mementos_.push_back(memento);
}

Memento Caretaker::getMemento(int index) const {
    if (index >= 0 && index < mementos_.size()) {
        return mementos_[index];
    }
    // return Memento("");
    // throw std::out_of_range("invalid index");
}