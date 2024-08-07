#include <iostream>
#include <bitset>

void foo1() {
    // std::cout << sizeof(long long) << std::endl;

    long long x1 = 1 << 32;
    std::cout << x1 << std::endl; // 0

    long long x2 = 1LL << 32;
    std::cout << x2 << std::endl; // 4294967296

    std::bitset<32> bit(65536);

    std::cout << bit << std::endl;

    double x3 = 2.3;

    float x = 1.1;
    float y = 2.2F;
}

enum LongLongEnum : long long {
    x1,
    x2
};

struct LongLongStruct {
    long long x1 : 8;
    long long x2 : 24;
    long long x3 : 32;
};



void foo2() {
    std::cout << sizeof(LongLongStruct) << std::endl;
    std::cout << sizeof(LongLongEnum) << std::endl;
    std::cout << sizeof(LongLongEnum::x1) << std::endl;
    std::cout << sizeof(LongLongEnum::x2) << std::endl;
}


// numeric_limits
#include <limits>
void foo3() {
    // macro
    std::cout << LLONG_MAX << std::endl;
    std::cout << LLONG_MIN << std::endl;
    std::cout << ULLONG_MAX << std::endl;

    // class template
    std::cout << std::numeric_limits<long long>::max() << std::endl;
    std::cout << std::numeric_limits<long long>::min() << std::endl;
    std::cout << std::numeric_limits<unsigned long long>::max() << std::endl;
}

int main() {
    // foo1();
    // foo2();
    // foo3();
    return 0;
}
