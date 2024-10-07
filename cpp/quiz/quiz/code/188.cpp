#include <iostream>

int main() {
    char *a = static_cast<char *>("Hello");
    a[4] = '\0';
    std::cout << a;
}