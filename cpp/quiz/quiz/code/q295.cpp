#include <iostream>

char a[2] = "0";

struct a_string {
    a_string() {
        std::cout << "a_string()" << std::endl;
        *a = '1';
    }
    ~a_string() {
        std::cout << "~a_string()" << std::endl;
        *a = '0';
    }
    const char *c_str() const { return a; }
};

void print(const char *s) {
    std::cout << s << std::endl;
}

a_string make_string() {
    return a_string{};
}

int main() {
    a_string s1 = make_string();
    print(s1.c_str());

    const char *s2 = make_string().c_str();
    print(s2);

    print(make_string().c_str());
}