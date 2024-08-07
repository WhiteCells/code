#include <iostream>

void Ignore() {
    /* 1 */
    for (int i = 0; i < 10; ) {
        std::cout << i++ << ' ';
    }
    std::cout << '\n';
    /* 2 */
    for (int i = 0; ; ) {
        std::cout << i++ << ' ';
        if (i > 9) {
            break;
        }
    }
    std::cout << '\n';
    int i = 0;
    /* 3 */
    for (; ; ) {
        std::cout << i++ << ' ';
        if (i > 9) {
            break;
        }
    }
    std::cout << '\n';
    i = 0;
    /* 4 */
    for (; i < 10; ) {
        std::cout << i++ << ' ';
    }
    std::cout << '\n';
    i = 0;
    /* 5 */
    for (; ; ++i) {
        std::cout << i << ' ';
        if (i > 8) {
            break;
        }
    }
    std::cout << '\n';
    i = 0;
    /* 6 */
    for (; i < 10; ++i) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    /* 7 */
    for (int i = 0; ; ++i) {
        std::cout << i << ' ';
        if (i > 8) {
            break;
        }
    }
    std::cout << '\n';
}


int main() {
    Ignore();
    return 0;
}