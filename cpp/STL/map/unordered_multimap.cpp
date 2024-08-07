#include <iostream>

#include <unordered_map>


void UseUnorderedMultimap() {
    std::unordered_multimap<int, int> mp;
    mp.emplace(1, 2);
    mp.emplace(1, 3);
    mp.emplace(1, 4);
    auto it = mp.find(1);
}


int main() {

    return 0;
}