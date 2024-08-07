#include <iostream>
#include <cstring>
#include <cstdio>

class Base {
public:
    Base() : str_(new char[12]) {
        strcpy(str_, "hello world");
        std::cout << "Base()" << std::endl;
    }
    Base(const Base &b) {
        std::cout << "Base(param)" << std::endl;
        str_ = new char[12];
        strcpy(str_, b.str_);
    }
    virtual ~Base() {
        std::cout << "~Base()" << std::endl;
        if (str_) {
            delete[] str_;
            str_ = nullptr;
        }
    }
    virtual char *getStr() {
        std::cout << "Base()::getStr()" << std::endl;
        return this->str_;
    }
protected:
    char *str_;
};

class Derived : public Base {
public:
    Derived() : Base() {
        std::cout << "Derived()" << std::endl;
    }
    Derived(const Derived &d) : Base(d) {
        std::cout << "Derived(const Derived &d)" << std::endl;
    }
    Derived(const Base &b) : Base(b) {
        std::cout << "Derived(const Base &b)" << std::endl;
    }
    ~Derived() {
        std::cout << "~Derived()" << std::endl;
        if (str_) {
            delete[] str_;
            str_ = nullptr;
        }
    }
    virtual char *getStr() override {
        std::cout << "Derived()::getStr()" << std::endl;
        return this->str_;
    }
};

int main() {
    Base *d_ptr = new Derived();
    // printf("%s\n", d_ptr->getStr());

    Base *d_ptr_copy = new Derived(*d_ptr);

    delete d_ptr;
    delete d_ptr_copy;

    return 0;
}