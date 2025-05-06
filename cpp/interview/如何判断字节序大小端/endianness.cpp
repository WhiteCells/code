#include <iostream>

// 机器的字节序
// 通过进行整数在内存中的字节顺序判断大小端

bool isBigEndian() {
    short i = 0x1234;
    return *(char *)&i == 0x12;
}

bool isBigEndian2() {
    short i = 1;
    return *(char *)&i != 1;
}

bool isLittleEndian() {
    short i = 0x1234;
    return *(char *)&i == 0x34;
}

int main(int argc, char *argv[]) {
    std::cout << "local endian: " << isBigEndian() << std::endl;
    std::cout << "local endian: " << isLittleEndian() << std::endl;

    int num = 0x12345678;
    char *p = (char *)&num;
    for (int i = 0; i < sizeof(num); ++i) {
        std::cout << std::hex << (int)*(p + i) << std::endl;
    }
    return 0;
}

// C++ 17
// #include <iostream>

// bool isLittleEndian() {
//     union {
//         uint32_t i;
//         char c[4];
//     } test = {0x01020304};

//     return test.c[0] == 0x04;
// }

// int main() {
//     if (isLittleEndian()) {
//         std::cout << "Little Endian\n";
//     } else {
//         std::cout << "Big Endian\n";
//     }

//     // 打印字节顺序
//     uint32_t num = 0x12345678;
//     char* p = reinterpret_cast<char*>(&num);
//     std::cout << "Memory layout: ";
//     for (size_t i = 0; i < sizeof(num); ++i) {
//         std::cout << std::hex << (static_cast<int>(static_cast<unsigned char>(p[i]))) << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }


// C++ 20
// #include <iostream>
// #include <bit>

// int main() {
// #if defined(__cpp_lib_endian)
//     if (std::endian::native == std::endian::little) {
//         std::cout << "Little Endian\n";
//     } else if (std::endian::native == std::endian::big) {
//         std::cout << "Big Endian\n";
//     } else {
//         std::cout << "Mixed/Unknown Endian\n";
//     }
// #else
//     std::cout << "std::endian not supported on this compiler.\n";
// #endif
// }

