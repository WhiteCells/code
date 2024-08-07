#include <iostream>
#include <X11/Xlib.h>

int main(int argc, char *argv[]) {
    int cnt = 0;
    for (int i = 0; i < 10000; ++i) {
        int *ptr = new int;
        if (0 == *ptr) {
            std::cout << *ptr << std::endl;
            ++cnt;
        }
        delete ptr;
    }
    std::cout << cnt << std::endl;
    return 0;
}