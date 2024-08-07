#include <iostream>

int fun() { return 0; }

void UseDecltype() {
    decltype(fun()) a = 10;
}

int main() {

    return 0;
}