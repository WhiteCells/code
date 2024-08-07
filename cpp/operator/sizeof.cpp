#include <iostream>

#include <iostream>
#include <cstring>
#include <vector>

int foo() {
    int a[10][2] {};
    std::cout << sizeof(a) << std::endl;
    std::cout << sizeof a << std::endl;
    char *str1 = "123";
    char str2[4] = "123";
    std::cout << sizeof(str1) << std::endl;
    std::cout << sizeof(str2) << std::endl;
    std::cout << strlen(str1) << std::endl;
    std::cout << strlen(str2) << std::endl;

    std::vector<int> v;
    std::cout << sizeof v << std::endl;
    return 0;
}

int main() {
    int arr[] = { 1, 2, 3, 4, 5, 6 };
    std::cout << sizeof(arr) / sizeof(arr[0]) << '\n';
    return 0;
}