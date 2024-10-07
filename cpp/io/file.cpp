#pragma once

#include <fstream>
#include <string>
#include <string_view>
#include <algorithm>
#include <iostream>

inline std::string file_get_content(std::string const &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::system_error(errno, std::generic_category());
    }
    return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

inline void file_put_content(std::string const &path, std::string_view content) {
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::system_error(errno, std::generic_category());
    }
    std::copy(content.begin(), content.end(), std::ostreambuf_iterator<char>(file));
}

int main(int argc, char *argv[])
{
    std::cout << file_get_content("./cerr.cpp") << std::endl;
    return 0;
}