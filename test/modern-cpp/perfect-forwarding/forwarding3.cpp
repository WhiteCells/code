#include <iostream>
#include <string>

template<class T>
void showType(T &&t) {
    std::cout << typeid(t).name() << std::endl;
    std::cout << std::is_same<T, std::string>() << std::endl;
    std::cout << std::is_same<T, std::string &>() << std::endl;
    std::cout << std::is_same<T, std::string &&>() << std::endl;
}

template<class T>
void perfectForwarding(T &&t) {
    // showType(static_cast<T &&>(t));
    // showType(std::move(t));
    // showType(std::forward<T>(t));
}

int main(int argc, char const *argv[]) {
    std::string str = "hello";
    perfectForwarding(str);
    perfectForwarding(std::string("world"));
    return 0;
}