#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

bool isPort(const char *port) {
    int len = strlen(port);
    for (int i = 0; i < len; ++i) {
        int c = *(port + i) - '0';
        if (c < 0 || c > 9) {
            return false;
        }
    }
    return true;
}

// ./script -p 8443
int main(int argc, char *argv[]) {
    std::string port {};
    if (argc >= 2) {
        if (!strcmp(argv[1], "-p")) {
            if (isPort(argv[2])) {
                port = argv[2];
            }
        }
    }
    std::cout << "port: " << port << std::endl;

    std::cout
        << "select host: " << std::endl
        << "1. world2.030215.xyz" << std::endl
        << "2. hello.030215.xyz" << std::endl;
    int x = 0;
    std::cout << "enter: ";
    std::cin >> x;
    std::string host {};
    switch (x) {
        default:
        case 1:
            host = "world2.030215.xyz";
            break;
        case 2:
            host = "hello.030215.xyz";
            break;
    }

    std::string url {"https://ipdb.api.030101.xyz/?type=bestcf"};
    std::string out {"./out.txt"};
    std::string res {"./res.txt"};
    char command[1024] {};
    sprintf(command, "curl %s -o %s", url.c_str(), out.c_str());
    system(command);

    std::string vless {};
    std::ifstream ifs {out};
    if (!ifs.is_open()) {
        std::cerr << out << " open failed" << std::endl;
        return EXIT_FAILURE;
    }
    std::ofstream ofs {res};
    std::string line {};
    std::cout << line << std::endl;
    while (std::getline(ifs, line)) {
        // 不能先找 sin_pos
        auto ip_pos_beg = vless.find('@') + 1;
        auto ip_len = vless.find(':', ip_pos_beg) - ip_pos_beg;
        vless.replace(ip_pos_beg, ip_len, line);

        if (!port.empty()) {
            auto port_pos_beg = vless.find(':', ip_pos_beg) + 1;
            auto port_len = vless.find('?', port_pos_beg) - port_pos_beg;
            vless.replace(port_pos_beg, port_len, port);
        }

        std::string pre_sni_str = "&sni=";
        int sni_pos = vless.find(pre_sni_str) + pre_sni_str.length();
        int sni_len = vless.find('&', sni_pos) - sni_pos;
        vless.replace(sni_pos, sni_len, host);
        // std::cout << vless << std::endl;

        std::string pre_host_str = "&host=";
        int host_pos = vless.find(pre_host_str) + pre_host_str.length();
        int host_len = vless.find('&', host_pos) - host_pos;
        vless.replace(host_pos, host_len, host);
        // std::cout << vless << std::endl;

        auto cd_pos_beg = vless.find('#') + 1;
        vless = vless.substr(0, cd_pos_beg);
        vless += line;
        ofs << vless << '\n';
    }
    ifs.close();
    ofs.close();

    std::string clipboard {"xsel --clipboard < "};
    clipboard += res;
    system(clipboard.c_str());
    std::cout << "cp config to clipboard" << std::endl;
    return 0;
}