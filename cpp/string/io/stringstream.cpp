#include <string>
#include <sstream>
#include <iostream>

void test01() {
    std::string str { "hello world" };
    
    // std::stringstream res_str(str);
    std::stringstream res_str;
    res_str << str;

    std::string word;
    while (res_str >> word) {
        std::cout << word << word.size() << std::endl;
    }
}

int main() {
    test01();
    return 0;
}