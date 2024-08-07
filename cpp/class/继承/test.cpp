#include <iostream>
#include <string>

class A {
public:
    std::string str_public = "A public string";

protected:
    std::string str_protected = "A protected string";

private:
    std::string str_private = "A private string";
};

class B : public A {
public:
    B() {
        str_public;
        str_protected;
    }
};

void fooB() {
    B b;
    b.str_public;
}

class C : protected A {
public:
    C() {
        str_public;
        str_protected;
    }

// protected:
//     A::str_public;
//     A::str_protected;
};

void fooC() {
    C c;
}

class D : private A {
public:
    D() {
        str_public;
        str_protected;
    }

// private:
//     A::str_public;
//     A::str_protected;
};

void fooD() {
    D d;
}

int main(int argc, char const *argv[]) {
    return 0;
}