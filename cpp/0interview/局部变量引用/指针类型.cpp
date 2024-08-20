#include <iostream>

// int *&get_error() {
//     int *a = new int {1};
//     return a;
// }

int *get() {
    int *a = new int {100};
    return a;
}

int main(int argc, char *argv[]) {
    // int *a = get_error();
    int *a = get();
    std::cout << *a << std::endl;
    delete a;
    return 0;
}