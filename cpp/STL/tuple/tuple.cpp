#include <iostream>
#include <string>

#include <tuple>


void UseTuple() {
    std::string name;
    int age;
    std::tuple<std::string&, int> t(name, age);
    std::get<0>(t) = "li";
    // std::get<1>(t) = 10;
    std::cout << name << '\n';
    // std::cout << age << '\n';
}


int main() {
    UseTuple();
    return 0;
}