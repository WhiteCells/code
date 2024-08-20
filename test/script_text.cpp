#include <string>
#include <iostream>

int main(int argc, char *argv[]) {
    std::string vless {};
    // replace 第二个参数是替换内容的长度
    vless.replace(vless.find('@') + 1, vless.find('?') - vless.find('@') - 1, "111.111.11.1");
    std::cout << vless << std::endl;

    vless = vless.substr(0, vless.find('#') + 1);
    vless += "111.1.1.1";
    std::cout << vless << std::endl;

    char c = '1';
    std::cout << c - '0' << std::endl;
    char c2 = 'a';
    std::cout << c2 - 'a' << std::endl;

    // std::cout << vless.find("&sni");
    // std::cout << *(vless.begin() + vless.find("&sni")) << std::endl;

    std::string pre_sni_str = "&sni=";
    int sni_pos = vless.find(pre_sni_str) + pre_sni_str.length() + 1;
    int sni_len = vless.find('&', sni_pos) - sni_pos;
    vless.replace(sni_pos, sni_len, "hhhh");
    std::cout << vless << std::endl;

    std::string pre_host_str = "&host=";
    int host_pos = vless.find(pre_host_str) + pre_host_str.length() + 1;
    int host_len = vless.find('&', host_pos) - host_pos;
    vless.replace(host_pos, host_len, "2-2-2.xyz");
    std::cout << vless << std::endl;

    return 0;
}