#include <iostream>
#include <algorithm>
#include <vector>
#include <string>


void test01() {
    std::vector<int> v;
    for (int i = 1; i < 11; ++i) { // must be orderly
        v.push_back(i);
    }
    int find_x = 9;
    bool res = std::binary_search(v.begin(), v.end(), find_x);
    std::cout << (res ? "exist" : "not exist") << std::endl;
}

int main() {
    test01();
    return 0;
}