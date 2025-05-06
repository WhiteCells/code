#include <memory>
#include <iostream>

class A {
public:
    A(int x) :
        x_(x) {
    }
    ~A() {
    }

    int get() const {
        return x_;
    }

private:
    int x_;
};

void foo1(std::shared_ptr<A> a) { // error
    a = std::make_shared<A>(10);
}

void foo2(std::shared_ptr<A> &a) {
    a = std::make_shared<A>(10);
}

int main(int argc, char *argv[]) {
    std::shared_ptr<A> a_ptr;
    // foo1(a_ptr);
    foo2(a_ptr);
    std::cout << a_ptr->get() << std::endl;
    return 0;
}