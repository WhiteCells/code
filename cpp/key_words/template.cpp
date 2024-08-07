#include <iostream>

template <class T1, class T2>
class Add {
private:
    T1 a;
    T2 b;
public:
    Add(T1 a, T2 b) : a(a), b(b) {
        std::cout << a + b << '\n';
    }
};

int main() {
    Add(1, 3);
    Add(1.1, 3);
    Add(1.1f, 1000);
}