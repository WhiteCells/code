#include <unordered_map>
#include <map>
#include <iostream>

int main(int argc, char *argv[]) {
    std::unordered_map<int, int> mp;
    mp[3] = 1;
    mp[2] = 1;

    for (const auto &iter : mp) {
        std::cout << iter.first << std::endl;
    }

    for (std::unordered_map<int, int>::iterator iter = mp.begin(); iter != mp.end(); ++iter) {
        std::cout << iter->first << std::endl;
    }

    std::map<int, int> mp2;
    mp2[3] = 1;
    mp2[2] = 1;
    for (const auto &iter : mp2) {
        std::cout << iter.first << std::endl;
    }
    
    return 0;
}