#include <iostream>
#include <vector>

#include <array>

void ArrayInt(){
    std::array<int, 10> a;
    // for (const auto& ele : a) {
    //     std::cout << ele << ' ';
    // }
    // std::cout << '\n';

    std::vector<std::array<int, 2>> va{ { 1, 2 }, { 2, 3 } };
    for(auto& [x, y] : va){
        std::cout << x << ' ' << y << ' ';
    }
}


int main(){
    ArrayInt();
    return 0;
}