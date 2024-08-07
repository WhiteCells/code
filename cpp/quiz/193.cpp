#include <iostream>

int main() {
    int a[] = <%1%>;
    int a2[] <%1%>;
    const char *str[] = <%<%"测试"%>,<%"测试"%>%>;
    const char *str2[] <%<%"测试"%>,<%"测试"%>%>;
    std::cout << a<:0:>;
    std::cout << str<:1:>;
}