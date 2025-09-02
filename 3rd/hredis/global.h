#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <iostream>
#include <functional>

#define ERROR(format, ...)                                      \
    do {                                                        \
        char buf[1024] {0};                                     \
        snprintf(buf, 1024, format, ##__VA_ARGS__);             \
        std::cerr << __func__ << " " << __LINE__;               \
        std::cerr << " ERROR: " << buf << std::endl;            \
    } while (0)                                                 \

#define INFO(format, ...)                                       \
    do {                                                        \
        char buf[1024] {0};                                     \
        snprintf(buf, 1024, format, ##__VA_ARGS__);             \
        std::clog << __func__ << " " << __LINE__                \
                  << "INFO: " << buf << std::endl;              \
    } while (0)                                                 \


class Defer {
public:
    Defer(const std::function<void()> &&func)
        : func_(std::move(func)) {
        
    }
    ~Defer() {
        func_();
    }
private:
    std::function<void()> func_;
};

#endif // _GLOBAL_H_