#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <mutex>

class Singleton {
public:
    static Singleton *getInstance();

private:
    Singleton() {}
    ~Singleton() {}

    class CleanUp {
    public:
        ~CleanUp() {
            if (Singleton::instance_) {
                delete Singleton::instance_;
                Singleton::instance_ = nullptr;
            }
        }
    };

    static Singleton *instance_;
    static std::mutex mutex_;

    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
};

#endif // _SINGLETON_H_