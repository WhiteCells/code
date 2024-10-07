// #include <iostream>

// int main(int argc, char *argv[]) {
//     // int x = 1, y = 1;
//     int x = 1;
//     // auto foo1 = [x, y] { return x + y; };
//     // auto foo2 = [&x, &y] { return x + y; };
//     // auto foo3 = [x] { x += 1 };
//     // auto foo4 = [x]() mutable { x += 1; return 0; } ();
//     // std::cout << foo4 << std::endl;
//     // std::cout << x << std::endl;

//     auto foo5 = [x] {
//         std::cout << std::is_same_v<decltype(x), const int> << std::endl;
//     };
//     foo5();
//     return 0;
// }

// #include <iostream>

// int main(int argc, char *argv[]) {
//     int x = 1;
//     // capture value
//     auto foo1 = [x]() mutable {
//         x += 1;
//         std::cout << x << std::endl;
//     };
//     foo1();
//     std::cout << x << std::endl;
//     return 0;
// }

// #include <iostream>

// int main(int argc, char *argv[]) {
//     int x = 1, y = 1;
//     auto foo = [x, &y]() mutable {
//         x += 1;
//         y += 1;
//         printf("%d %d\n", x, y);
//     };
//     foo();
//     printf("%d %d\n", x, y);
//     foo();
//     printf("%d %d\n", x, y);
//     return 0;
// }

// #include <iostream>

// int main(int argc, char *argv[]) {
//     int x = 1, y = 1;
//     auto foo = [x, &y]() mutable {
//         x += 1;
//         y += 1;
//         printf("%d %d\n", x, y);
//     };
//     x = 10;
//     y = 10;
//     foo();
//     return 0;
// }


#include <iostream>

class A {
public:
    void print() { printf("%d\n", x); }
    void test() {
        auto foo = [this] {
            print();
        };
        x = 10;
        foo();
    }

private:
    int x;
};

void foo() {}

int main(int argc, char *argv[]) {
    A a;
    a.test();


    return 0;
}