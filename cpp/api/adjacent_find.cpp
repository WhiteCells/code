#include <iostream>
#include <vector>
#include <algorithm>


void test() {
    std::vector<int> v {10, 20, 30, 40, 40, 20, 30, 30};

    auto it = adjacent_find(v.begin(), v.end());
    if (it != v.end()) {
        std::cout << *it << std::endl;
    } else {
        std::cout << "no find" << std::endl;
    }
}

int main() {
    test();
    return 0;
}