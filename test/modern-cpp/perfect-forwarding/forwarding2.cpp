#include <iostream>
#include <string>

template<class T>
void showType(T t) {
    std::cout << typeid(t).name() << std::endl;
}

template<class T>
void normalForwarding(const T &t) {
    t = "world"; // compilation failed
    showType(t);
}

int main(int argc, char const *argv[]) {
    std::string str = "hello";
    normalForwarding(str);
    return 0;
}