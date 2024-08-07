#include <thread>
#include <iostream>
#include <string>

// void foo(int i, const std::string &s) {
//     std::cout << s << i << std::endl;
// }

// void oops() {
//     char buff[6] {"hello"};
//     std::thread my_thread(foo, 1, buff);
//     my_thread.detach();
// }

// int main(int argc, char *argv[]) {
//     char buff[6] {"hello"};
//     // std::thread my_thread(foo, 1, buff);
//     std::thread my_thread(foo, 1, std::string(buff));
//     my_thread.detach();
//     return 0;
// }

void foo(int &i) {
    i = 0;
}

int main(int argc, char *argv[]) {
    int i = 1;
    // std::thread my_thread(foo, i); // 编译错误
    std::thread my_thread(foo, std::ref(i));
    my_thread.detach();
    std::cout << i << std::endl;
    return 0;
}