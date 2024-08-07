#include "singleton.h"

// .cpp 文件实现
Singleton *Singleton::instance_ = nullptr;

Singleton *Singleton::getInstance() {
    // 静态变量，程序结束时调用其析构
    static CleanUp cleanup;

    if (!instance_) {
        instance_ = new Singleton();
    }
    return instance_;
}