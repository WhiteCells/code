#include <iostream>
#include <bitset>

int main(){
    std::bitset<4> b;

    std::cout << b << "\n";
    std::cout << b.flip(0) << '\n';
    std::cout << b.flip(2) << '\n';
    std::cout << b.flip() << '\n';
}