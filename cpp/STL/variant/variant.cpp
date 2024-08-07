#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <variant> // C++17

void foo() {
    std::vector<std::variant<int, double, float, std::string>> v;
    v.push_back(1);
    v.push_back(1.1);
    v.push_back("test");
}


int main() {
    
}