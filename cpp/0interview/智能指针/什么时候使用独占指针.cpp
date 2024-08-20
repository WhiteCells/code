#include <iostream>
#include <memory>
#include <string>

class A2 {
public:
    A2(const std::string &obj) : obj_(obj) {
        std::cout << obj << __func__ << std::endl;
        // obj life cycle end
        // ref to obj_ does not exist
    }
    ~A2() {
        std::cout << obj_ << __func__ << std::endl;
    }

private:
    const std::string &obj_;
};

class A {
public:
    A(const std::string &obj) : obj_(obj) {
        std::cout << obj << __func__ << std::endl;
    }
    ~A() {
        std::cout << obj_ << __func__ << std::endl;
    }

private:
    std::string obj_;
};

int main(int argc, char *argv[]) {
    std::unique_ptr<A> a_ptr = std::make_unique<A>("a_ptr");
    a_ptr = std::make_unique<A>("a_ptr2");
    a_ptr.reset();
    std::cout << "---" << std::endl;
    return 0;
}