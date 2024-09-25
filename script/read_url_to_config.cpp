#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

int main(int argc, char *argv[]) {
    std::string url{"https://addapit.ssorg.us.kg/addressesapi.txt?token=SM2024818"};
    std::string url_out_path{"./url_out"};
    std::string config_out_path{"./config.txt"};
    std::string config{
        "vless://25b56f1b-1691-42c8-88a6-ee765fb55fba"
        "@47.243.234.9:8443?"
        "security=tls&sni=world2.030215.xyz&fp=random&type=ws&path=/?ed%3D2560&host=world2.030215.xyz&encryption=none"
        "#59%20ms-17821%20kB/s"};

    std::stringstream ss;
    ss << "curl " << url << " -o " << url_out_path;
    std::string command_str{ss.str()};
    std::cout << command_str << std::endl;

    system(command_str.c_str());

    std::ifstream ifs(url_out_path);
    if (!ifs.is_open()) {
        std::cerr << "open " << url_out_path << " failed" << std::endl;
        return EXIT_FAILURE;
    }
    std::ofstream ofs(config_out_path);

    std::string line;
    int cnt = 0;
    while (std::getline(ifs, line)) {
        std::size_t seg_pos = line.find('#');
        std::string ip = line.substr(0, seg_pos);
        std::string comment = line.substr(seg_pos + 1, line.size() - 1 - seg_pos);

        // replace
        std::size_t ip_beg = config.find('@') + 1;
        std::size_t ip_end = config.find('?');
        std::size_t ip_len = ip_end - ip_beg;
        config.replace(ip_beg, ip_len, ip);

        std::size_t comment_beg = config.find_last_of('#') + 1;
        std::size_t comment_end = config.size();
        std::size_t comment_len = comment_end - comment_beg;
        config.replace(comment_beg, comment_len, comment);

        ofs << config << std::endl;
        ++cnt;
    }

    ifs.close();
    ofs.close();

    std::string clipboard{"xsel --clipboard < "};
    clipboard += config_out_path;
    system(clipboard.c_str());
    std::cout << "\ncopy " << cnt << " config to clipboard " << std::endl;
    return 0;
}