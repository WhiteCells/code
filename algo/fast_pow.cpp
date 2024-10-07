#include <iostream>

int pow(int x, int y)
{
    int res = 1;
    while (y) {
        if (y & 1) {
            res *= x;
        }
        x *= x;
        y >>= 1;
    }
    return res;
}

int main(int argc, char *argv[])
{
    std::cout << pow(2, 5) << std::endl;
    return 0;
}