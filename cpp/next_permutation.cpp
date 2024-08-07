#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[]) {
    std::vector<int> v {1, 2, 3};
    // 1 2 3
    // 1 3 2
    // 2 1 3
    // 2 3 1
    // 3 2 1
    // 3 1 2
    while (std::next_permutation(v.begin(), v.end())) {
        std::cout << "has" << std::endl;
    }

    // n! / (n - m)!
    std::vector<int> v2 {1};
    while (std::next_permutation(v2.begin(), v2.end())) {
        std::cout << "has2" << std::endl;
    }
    return 0;
}