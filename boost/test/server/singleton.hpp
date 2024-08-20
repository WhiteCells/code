#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <memory>
#include <mutex>
#include <iostream>

template<typename T>
class Singleton {
public:
    ~Singleton();
    static std::shared_ptr<T> getInstance();

protected:
    Singleton() = default;
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

private:
    static std::shared_ptr<T> instance_;
};

template<typename T>
std::shared_ptr<T> Singleton<T>::instance_ = nullptr;

template<typename T>
Singleton<T>::~Singleton() {
    std::cout << __func__ << std::endl;
}

template<typename T>
std::shared_ptr<T> Singleton<T>::getInstance() {
    static std::once_flag once;
    std::call_once(once, [&]() {
        instance_ = std::shared_ptr<T>(new T());
    });
    return instance_;
}

#endif // _SINGLETON_H_