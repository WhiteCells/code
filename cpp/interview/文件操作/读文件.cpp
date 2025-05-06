#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    std::ifstream ifs("./message.txt");
    if (!ifs.is_open()) {
        std::cerr << "open failed" << std::endl;
        return EXIT_FAILURE;
    }
    std::string line;
    while (std::getline(ifs, line)) {
        std::cout << line << std::endl;
    }
    ifs.close();
    return 0;
}