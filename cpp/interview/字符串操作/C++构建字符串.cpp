#include <iostream>
#include <string>
#include <cstring>

int main(int argc, char *argv[]) {
    const char *data = "message";
    short data_len = strlen(data); // 7
    std::string data_str1 = std::string(data);
    // 不包含 '\0'
    std::cout << data_str1.size() << std::endl;

    std::string str1 = std::string("message");
    std::cout << str1.size() << std::endl;
    std::cout << str1.length() << std::endl;

    std::string data_str2 = std::string(data, data_len);
    std::cout << data_str2.size() << std::endl;
    return 0;
}