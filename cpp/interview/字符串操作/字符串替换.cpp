#include <string>
#include <iostream>
#include <fstream>

// vless://25b56f1b-1691-42c8-88a6-ee765fb55fba@
// 104.21.25.97:2087
// ?security=tls&sni=world2.030215.xyz&fp=random&type=ws&path=/?ed%3D2560&host=world2.030215.xyz&encryption=none#
int main(int argc, char *argv[]) {
    std::string str {"12345678"};
    str.replace(str.find('2'), str.find('5'), "0");
    std::cout << str << std::endl;

    // std::ifstream fs("./bestcf_file.txt");
    std::ifstream fs("./");
    std::string line;
    while (std::getline(fs, line)) {
        std::cout << line << std::endl;
    }
    fs.close();
    return 0;
}