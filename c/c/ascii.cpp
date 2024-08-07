#include <iostream>

// leeter char
void Letter() {
    char c1 = 'a', c2 = 'z';
    char c3 = 'A', c4 = 'Z';
    std::cout << "a ASCII:" << static_cast<int>(c1) << '\n';
    std::cout << "z ASCII:" << static_cast<int>(c2) << '\n'; // a~z : 97~122
    std::cout << "A ASCII:" << static_cast<int>(c3) << '\n';
    std::cout << "Z ASCII:" << static_cast<int>(c4) << '\n'; // A~Z : 65~90
}

// digit char
void Digit() {
    char c0 = '0', c1 = '1', c2 = '2', c3 = '3', c4 = '4', c5 = '5'
        , c6 = '6', c7 = '7', c8 = '8', c9 = '9';

}

// special characters
void Special() {
    char c = ' ';
    std::cout << "space ASCII:" << static_cast<int>(c) << '\n'; // space : 32

    char c1  = '!';
    char c2  = '@';
    char c3  = '#';
    char c4  = '$';
    char c5  = '%';
    char c6  = '^';
    char c7  = '&';
    char c8  = '*';
    char c9  = '(';
    char c10 = ')';
    char c11 = '-';
    char c12 = '_';
    char c13 = '=';
    char c14 = '+';
}

int main() {
    Letter();
    Special();
    return 0;
}
