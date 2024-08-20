#include <iostream>

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