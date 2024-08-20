#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    std::ofstream ofs("./message.txt"); // 默认截断文件
    if (!ofs.is_open()) {
        std::cerr << "open err" << std::endl;
        return EXIT_FAILURE;
    }
    ofs << "new line1_1\n";
    ofs << "new line1_2\n";
    ofs << "new line1_3\n";
    ofs.close();

    // 添加标记的方式
    std::ofstream ofs2("./message.txt", std::ios::app);
    if (!ofs2.is_open()) {
        std::cerr << "open err" << std::endl;
        return EXIT_FAILURE;
    }
    ofs2 << "new line2_1\n";
    ofs2 << "new line2_2\n";
    ofs2 << "new line2_3\n";
    ofs2.close();

    // 修改文件指针的方式
    std::ofstream ofs3("./message.txt", std::ios::app);
    if (!ofs3.is_open()) {
        std::cerr << "open err" << std::endl;
        return EXIT_FAILURE;
    }
    ofs.seekp(0, std::ios::end);
    ofs3 << "new line3_1\n";
    ofs.seekp(0, std::ios::end);
    ofs3 << "new line3_2\n";
    ofs.seekp(0, std::ios::end);
    ofs3 << "new line3_3\n";
    ofs3.close();

    return 0;
}