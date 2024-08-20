#include <iostream>

class A {
public:
    A(int a) {}
    A(const A &) = delete;
    const A &operator=(const A &) = delete;
    ~A() { std::cout << "~A()" << std::endl; }
};

class Server {
public:
    Server(A &a) : a1(a), a2(a) {}
    // Server(A &a) : a1(a), a2(a1) {}

private:
    A &a1;
    A &a2;
};

int main(int argc, char *argv[]) {
    A a {1};
    Server server(a);
    std::cout << "---" << std::endl;
    return 0;
}