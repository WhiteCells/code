#include <iostream>
struct X {
    X() {
        std::cout << "X";
    }
};

int main() {
    X x(); // this is a function declaration
}