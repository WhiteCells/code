#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    std::string path {};
    if (argc == 2) {
        path = std::string(argv[1]);
    }
    std::cout << path << std::endl;

    std::string str = "@1.1.1.1:443???";
    int ip_begin = str.find('@') + 1;
    int ip_end = str.find(':', ip_begin);
    str.erase(ip_begin, ip_end - ip_begin);
    // for (int i = ip_begin; str[i] != ':'; ++i) {
    //     str.erase(i);
    // }
    std::cout << str << std::endl;

    str.insert(ip_begin, "127.0.0.1");
    std::cout << str << std::endl;

    int port_begin = str.find(':') + 1;
    int port_end = str.find('?', port_begin);
    str.erase(port_begin, port_end - port_begin);
    std::cout << str << std::endl;

    str.insert(port_begin, "22");
    std::cout << str << std::endl;

    return 0;
}