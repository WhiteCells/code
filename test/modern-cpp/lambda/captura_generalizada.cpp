// #include <iostream>
// #include <functional>

// class A {
// public:
//     A() {}
//     A(A &&) {
//         std::cout << "move construct" << std::endl;
//     }
//     A(const A &) {
//         std::cout << "copy construct" << std::endl;
//     }
// };

// int main(int argc, char *argv[]) {
//     A a;
//     std::cout << &a << std::endl;
//     std::function<void()> foo = [a = std::move(a)] {
//         std::cout << &a << std::endl;
//     };
//     foo();
//     return 0;
// }

#include <iostream>
#include <future>

class Work {
public:
    Work() : value_(1) {}
    // std::future<int> spawn() {
    //     return std::async([=]() \
    //         -> int {return value_;});
    // }
    std::future<int> spawn() {
        return std::async([=, tmp = *this]() \
            -> int { return tmp.value_; });
    }
private:
    int value_;
};

std::future<int> foo() {
    Work work;
    return work.spawn();
}

int main(int argc, char *argv[]) {
    std::future<int> f = foo();
    f.wait();
    std::cout << "f.get() = " << f.get() << std::endl;
    return 0;
}
