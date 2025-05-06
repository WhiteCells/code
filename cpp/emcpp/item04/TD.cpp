#include <iostream>
#include <string>

template<typename T>
class TD;

int main() {
    const int *a = nullptr;
    TD<decltype(*a)> a_type;
    
    int b = 10;
    TD<decltype(b)> b_type;
}