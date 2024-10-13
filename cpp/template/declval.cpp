#include <iostream>
#include <utility>  // for std::declval
#include <type_traits>  // for std::is_same

class MyClass {
public:
    int getValue() { return 42; }
};

template <typename T>
auto get_return_type() -> decltype(std::declval<T>().getValue()) {
    return std::declval<T>().getValue();
}

int main() {
    // 使用 decltype 来推导 getValue() 的返回类型
    static_assert(std::is_same_v<decltype(get_return_type<MyClass>()), int>);
    std::cout << "The return type of getValue() is int." << std::endl;
}