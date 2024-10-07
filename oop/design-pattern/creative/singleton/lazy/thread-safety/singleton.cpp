#include "singleton.h"

Singleton *Singleton::instance_ = nullptr;

std::mutex Singleton::mutex_;

Singleton *Singleton::getInstance() {
    static CleanUp cleanup;
    if (instance_ == nullptr) {
        mutex_.lock();
        if (instance_ == nullptr) {
            instance_ = new Singleton();
        }
        mutex_.unlock();
    }
    return instance_;
}