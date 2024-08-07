#include <unordered_map>
#include <string>
#include <iostream>

int main(int argc, char *argv[]) {
    std::unordered_map<std::string, std::string> mp;
    mp["key"] = "val";
    mp["key2"] = "val2";
    for (const auto &item : mp) {
        std::cout << item.first << " "
            << item.second << std::endl;
    }
    return 0;
}