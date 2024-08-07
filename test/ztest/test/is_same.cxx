// #include <iostream>

// int main(int argc, char *argv[]) {
//     unsigned int a = 1;
//     unsigned b = 2;
//     double c = 2;
//     std::cout << std::is_same<decltype(a), decltype(c)>::value << std::endl;
//     return 0;
// }

#include <iostream>

class A {
public:
    int getA() const {
        return a_;
    }
    int &getA() {
        return a_;
    }
    void setA(int &&x) {
        a_ = x;
    }
private:
    int a_;
};

template<typename T>
T foo(T a) {

}

int main(int argc, char *argv[]) {
    A a;
    // const A a2;
    a.getA() = 1;
    a.getA() = 2;
    a.setA(1);
    int v = 1;
    // a.setA(v);
    return 0;
}