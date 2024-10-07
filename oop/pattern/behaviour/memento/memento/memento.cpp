#include "memento.h"

Memento::Memento(std::string state)
    : state_(state) {

}

void Memento::setState(const std::string &state) {
    state_ = state;
}

std::string Memento::getState() const {
    return state_;
}