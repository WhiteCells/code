#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <iostream>

class Singleton {
public:
    static Singleton *getInstance();

private:
    Singleton() {}
    ~Singleton() {}
    static Singleton *instance_;

    // 嵌套类，用于删除动态分配的单例
    class CleanUp {
    public:
        ~CleanUp() {
            if (Singleton::instance_) {
                delete Singleton::instance_;
                instance_ = nullptr;
            }
        }
    };

    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
};

#endif // _SINGLETON_H_