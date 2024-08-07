#include <iostream>
#include <map>
#include <tuple>
#include <unordered_map>

void foo() {
    std::map<int, int> mp;

    mp.insert({1, 2});
    mp.insert({1, 3}); // insert failed

    mp.insert(std::pair<int, int>(1, 2));
    mp.insert(std::pair(1, 2));
    mp.insert(std::pair {1, 2});
    mp.insert({1, 2});
    mp.insert(std::make_pair<int, int>(1, 2));
    mp.insert(std::make_pair(1, 2));

    for (const auto &[k, v] : mp) {
        std::cout << k << ' ' << v << std::endl;
    }

}

int main(int argc, char const *argv[]) {
    foo();
    return 0;
}