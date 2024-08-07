#include <iostream>

// void foo(int *) {}
// void foo(int *const) {}

// void foo(const int *) {}
// void foo(const int *const) {}

void foo(int) {}
// void foo(const int) {}
void foo(int &) {}
// void foo(const int &) {}



void test1() {
    int a = 0;
    // foo(a);

    const int b = 0;
    foo(b);
}

int main(int argc, char *argv[]) {
    test1();
    return 0;
}