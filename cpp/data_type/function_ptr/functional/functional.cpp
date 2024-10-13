#include <functional>
#include <iostream>

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

int main(int argc, char *argv[]) {
    {
        Defer defer([]() {
            std::cout << "===" << std::endl;
        });
        std::cout << "###" << std::endl;
    }
    std::cout << "@@@" << std::endl;
    return 0;
}