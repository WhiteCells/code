#include <iostream>
#include <algorithm>
#include <vector>

bool isPositive2(int a) {
    return a > 0;
}

int main(int argc, char *argv[]) {
    std::vector<int> v {-1, 0, 1};

    struct isPositive1 {
        bool operator()(int a) {
            return a > 0;
        }
    };

    auto iter1 = std::find_if(v.begin(), v.end(), isPositive1());
    auto iter2 = std::find_if(v.begin(), v.end(), isPositive2);
    auto iter3 = std::find_if(v.begin(), v.end(), [](int a) { return a > 0; });

    std::cout << *iter1 << std::endl;
    std::cout << *iter2 << std::endl;
    std::cout << *iter3 << std::endl;
    return 0;
}