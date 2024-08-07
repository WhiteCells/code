#include <iostream>
#include <memory>

class Singleton {
public:
    // static std::shared_ptr<Singleton> getInstance() {
    //     if (!instance_) {
    //         // 使用 make_shared 可能会导致问题
    //         instance_ = std::make_shared<Singleton>();
    //         // 使用 new 是安全的
    //         // instance_ = std::shared_ptr<Singleton>(new Singleton);
    //     }
    //     return instance_;
    // }
    static std::shared_ptr<Singleton> getInstance() {
        // static auto instance = std::shared_ptr<Singleton>(new Singleton());
        // error
        static auto instance = std::make_shared<Singleton>();
        // static auto instance = std::make_shared<Singleton>(new Singleton());
        return instance;
    }
private:
    Singleton() {}
    static std::shared_ptr<Singleton> instance_;
};

std::shared_ptr<Singleton> Singleton::instance_;

int main(int argc, char *argv[]) {
    Singleton::getInstance();
    return 0;
}