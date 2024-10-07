#include "subject.h"
#include <vector>
#include <algorithm>
#include <iostream>

class ConcreteSubject : public Subject {
public:
    ~ConcreteSubject() {
        for (auto &observer : observers_) {
            if (observer) {
                delete observer;
                observer = nullptr;
            }
        }
    }

    virtual void attach(Observer *observer) override {
        observers_.push_back(observer);
    }

    virtual void detach(Observer *observer) override {
        auto iter = std::find(observers_.begin(), observers_.end(), observer);
        if (iter != observers_.end()) {
            observers_.erase(iter);
            delete *iter;
            *iter = nullptr;
        }
    }

    virtual void notify() override {
        for (const auto &observer : observers_) {
            observer->update();
        }
    }

    void stateChanged() {
        std::cout << "state changed" << std::endl;
        notify();
    }

private:
    std::vector<Observer *> observers_;
};