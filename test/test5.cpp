// #include <iostream>

// int main() {
//     int j = 1;
//     int &i = j, j;
//     j = 2;
//     std::cout << i << j;
// }

#include <iostream>

int j = 1;

int main(int argc, char *argv[]) {
    int &i = j, j;
    j = 2;
    std::cout << i << j;
}

