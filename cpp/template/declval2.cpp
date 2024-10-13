#include <iostream>
#include <type_traits>
#include <utility>

struct A {
    int getValue() { return 42; }
};

struct B {
    // double getValue() { return 3.14; }
};

template <typename T>
auto has_getValue(int) -> decltype(std::declval<T>().getValue(), std::true_type());

template <typename T>
std::false_type has_getValue(...);

int main() {
    std::cout << "A has getValue: " << decltype(has_getValue<A>(0))::value << std::endl;
    std::cout << "B has getValue: " << decltype(has_getValue<B>(0))::value << std::endl;
}
