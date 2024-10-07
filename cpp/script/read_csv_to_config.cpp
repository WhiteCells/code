#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

/**
 * if (0 == cnt) {
 *     ip = cell;
 * } else if (1 == cnt) {
 *     port = cell;
 * } else if (6 == cnt) {
 *     delay = cell;
 * } else if (7 == cnt) {
 *     speed = cell;
 * }
 */
#define IP_CELL     0
#define PORT_CELL   1
#define DELAY_CELL  6
#define SPEED_CELL  7

int main(int argc, char *argv[]) {
    std::string url {};
    std::string csv_path {};
    std::string delay_require {"100"};
    std::string speed_require {"8000"};
    if (argc == 1) {
        std::cout << "Enter .csv file path: ";
        std::getline(std::cin, csv_path);
    } else if (argc == 2) {
        csv_path = argv[1];
    } else if (argc >= 4) {
        delay_require = std::string(argv[2]);
        speed_require = std::string(argv[3]);
    }

    std::ifstream csv_file(csv_path);
    if (!csv_file.is_open()) {
        std::cout << "open failed!!!\n";
        return -1;
    }

    std::ofstream out_file("./out.txt", std::ios::out);

    std::string line;
    int row = 0; // jump one row
    while (std::getline(csv_file, line)) {
        if (0 == row) {
            ++row;
            continue;
        }
        std::stringstream ss(line);

        std::string ip {}; // 0
        std::string port {}; // 1
        std::string delay {}; // 6
        std::string speed {}; // 7

        int cnt = 0; // current col
        bool flag = false;
        std::string cell {};
        while (getline(ss, cell, ',')) {
            switch (cnt) {
                case IP_CELL:
                    ip = cell;
                    break;
                case PORT_CELL:
                    port = cell;
                    break;
                case DELAY_CELL:
                    delay = cell;
                    break;
                case SPEED_CELL:
                    speed = cell;
                    break;
                default:
                    break;
            }
            ++cnt;
            if (!delay.empty() && !speed.empty()) {
                int delay_num = stoi(delay);
                int speed_num = stoi(speed);
                if (delay_num <= std::stoi(delay_require)
                    && speed_num >= std::stoi(speed_require)) {
                    flag = true;
                    // std::cout << delay_num << " " << speed_num << std::endl;
                }
            }
        }

        std::string cur = url;
        if (flag) {
            std::size_t ip_begin = cur.find('@');
            cur.insert(ip_begin + 1, ip);
            std::size_t port_begin = cur.find(':', ip_begin);
            cur.insert(port_begin + 1, port);
            std::size_t comment_begin = cur.find('#', port_begin);
            cur.insert(comment_begin + 1, delay + "-" + speed);
            // std::cout << cur << std::endl;
            out_file << cur << "\n";
        }
    }

    out_file.close();
    csv_file.close();

    system("xsel --clipboard < ./out.txt");

    std::cout << "cp config to clipboard" << std::endl;
    return 0;
}