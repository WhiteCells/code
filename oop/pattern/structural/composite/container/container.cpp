#include "container.h"

Container::~Container() {
    for (auto &iter : children_) {
        if (iter.second) {
            delete iter.second;
            iter.second = nullptr;
        }
    }
    children_.clear();
}

void Container::move(double x, double y) {
    for (auto &iter : children_) {
        iter.second->move(x, y);
    }
}

void Container::draw() {
    for (const auto &iter : children_) {
        iter.second->draw();
    }
}

bool Container::add(int id, Graphic *graphic) {
    if (children_.count(id)) {
        return false;
    }
    children_[id] = graphic;
    return true;
}

bool Container::remove(int id) {
    if (!children_.count(id)) {
        return false;
    }
    children_.erase(id);
    return true;
}