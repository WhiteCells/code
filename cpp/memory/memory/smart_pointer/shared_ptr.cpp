#include <memory>
#include <iostream>
#include <map>
#include <string>

class A {
public:
    A(int a) : a_(a) { std::cout << "A()" << std::endl; }
    A(const A &) { std::cout << "A(const A &)" << std::endl; }
    ~A() { std::cout << "~A()" << std::endl; }

    void set(int a) { a_ = a; };
    void print() { std::cout << a_ << std::endl; }
    
private:
    int a_;
};

void foo(A *a) {
    a->set(300);
    delete a;
}

int main(int argc, char *argv[]) {
    std::map<std::string, std::shared_ptr<A>> mp;
    mp["1"] = std::make_shared<A>(1);
    mp["2"] = std::make_shared<A>(2);
    mp["3"] = std::make_shared<A>(3);
    for (auto &item : mp) {
        std::shared_ptr<A> p = item.second;
        item.second.reset();
    }

    std::cout << "====" << std::endl;

    A *a1 = new A(100);
    A *a2 = a1;
    a1->print();
    a2->print();

    // a2->set(200);
    foo(a2);

    a1->print();
    a2->print();

    return 0;
}