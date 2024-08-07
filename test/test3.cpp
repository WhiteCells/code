#include <iostream>
#include <string>
#include <inttypes.h>
#include <sstream>

// 应该使用组合而不是进程，标准库的类没有析构函数
class MyString : public std::string {
public:
    int toInt() {
        int res = 0;
        for (const auto &c : *this) {
            if (std::isalpha(c)) {
                return -1;
            }
            res = res * 10 + (c - '0');
        }
        return res;
    }

    int toInt2() {
        std::istringstream iss(*this);
        int res;
        iss >> res;
        return res;
    }
};

int main(int argc, char *argv[]) {
    MyString str {"hello world"};
    std::cout << str << std::endl;

    MyString str2 {"123"};
    std::cout << str2.toInt() << std::endl;
    std::cout << str2.toInt2() << std::endl;

    MyString str3 {"123a"};
    std::cout << str3.toInt() << std::endl;
    std::cout << str3.toInt2() << std::endl;
    return 0;
}