#include <iostream>

auto foo() -> void {} // void foo() {}

int func(char x) { return x; }

typedef int (*pf)(char);
pf foo2() {
    return func;
}

auto foo3() -> int(*)(char) {
    return func;
}

// template of sum
template<class T1, class T2>
auto sum(T1 a, T2 b) -> decltype(a + b) {
    return a + b;
}

void foo4() {
    std::cout << sum(1, 2.2) << std::endl;
}

template<class T1, class T2>
decltype(T1() + T2()) sum2(T1 a, T2 b) {
    return a + b;
}

void foo5() {
    std::cout << sum2(1, 2.3) << std::endl;
}

template<class T>
class IntWrap {
    friend std::ostream &operator<<(std::ostream &os, const IntWrap<T> &i) {
        os << i.n_;
        return os;
    }
public:
    IntWrap(T n) : n_(n) {}
    IntWrap operator+(const IntWrap &other) {
        return IntWrap(n_ + other.n_);
    }
private:
    T n_;
};

template<class T1, class T2>
decltype(*static_cast<T1 *>(nullptr) + *static_cast<T2 *>(nullptr))
sum3(T1 a, T2 b) {
    return a + b;
}

template<class T>
T &&declval();

template<class T1, class T2>
decltype(declval<T1>() + declval<T2>())
sum4(T1 a, T2 b) {
    return a + b;
}

void foo6() {
    std::cout << sum3(IntWrap(1), IntWrap(2))
        << " "
        << sum4(IntWrap(1.1), IntWrap(2.2));
}

int main(int argc, char const *argv[]) {

    // foo4();
    // foo5();
    // foo6();

    int a = 1;
    decltype(a++) b = 1;
    decltype(++a) c = a;
    std::cout << a << std::endl;
    return 0;
}