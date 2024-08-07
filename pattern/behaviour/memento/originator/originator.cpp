#include "originator.h"

Originator::Originator(std::string state)
    : state_(state) {

}

void Originator::setState(const std::string &state) {
    state_ = state;
}

std::string Originator::getState() const {
    return state_;
}

Memento Originator::createMemento() {
    return Memento(state_);
}

void Originator::restoreFromMemento(const Memento &memento) {
    state_ = memento.getState();
}