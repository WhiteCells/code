#include <iostream>

#define PS char *

using ps1 = char *;
typedef char *ps2;

int main(int argc, char *argv[]) {
    const ps1 p1;
    const ps2 p2;
    const PS p2;
    return 0;
}