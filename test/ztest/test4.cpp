#include <iostream>

void print(char const *str) { std::cout << str; }
void print(short num) { std::cout << num; }
void print(int num) { std::cout << num; }

int main() {
    print(0);
}