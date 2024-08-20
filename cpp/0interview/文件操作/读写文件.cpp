#include <iostream>
#include <fstream>

// std::ios::app   每次写入时将自动将数据追加到文件末尾
// std::ios::ate   打开文件时，直接将写指针移至文件末尾
// std::ios::in    读文件标记
// std::ios::out   写文件标记

// seekp(off_type offset, std::ios_base::seekdir dir);
// offset
// 偏移位置
// dir
// std::ios_base::beg
// std::ios_base::cur
// std::ios_base::end

int main(int argc, char *argv[]) {
    // std::fstream fs("./message.txt", std::ios::in | std::ios::out | std::ios::app);
    std::fstream fs("./message.txt", std::ios::in | std::ios::out);
    if (!fs.is_open()) {
        std::cerr << "open err" << std::endl;
        return EXIT_FAILURE;
    }
    fs.seekp(0, std::ios::end);
    fs << "new line1_1\n";
    fs << "new line1_2\n";
    fs << "new line1_3\n";

    std::string line;
    fs.seekp(0, std::ios::beg);
    while (std::getline(fs, line)) {
        std::cout << line << std::endl;
    }

    // while (fs >> line) { // 空格
    //     std::cout << line << std::endl;
    // }

    fs.close();
    return 0;
}