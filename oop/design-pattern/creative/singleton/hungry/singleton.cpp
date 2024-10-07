#include "singleton.h"

Singleton *Singleton::instance_ = new Singleton();

Singleton *Singleton::getInstance() {
    static CleanUp cleanup;
    return instance_;
}