#include <iostream>

template<typename ...Ts>
struct X {
    X(Ts ...args) : Var(0, args...) {
        std::cout << Var;
    }

    int Var;
};

int main(int argc, char *argv[]) {
    X<> x;
}

/*
First, let's have a look at the initialization of X::Var. Var(0, args...)
is valid if there are no template arguments, since then it's just Var(0).
If there however are any template arguments, they expand to an invalid initializer for int,
such as Var(0, arg1, arg2). So the only valid specialization of X is the one with no arguments.

X<> x in fact does just that, it instantiates the template with no arguments, which would be valid.

However, §[temp.res]¶8.2 says:

[if] every valid specialization of a variadic template requires an empty template parameter pack
[the program is ill-formed, no diagnostic required.]

As we've seen, the only valid specialization requires an empty template parameter pack,
so the program is ill-formed, no diagnostic required. When no diagnostic is required,
the compiler is not required to diagnose the error,
but execution of the program is undefined.
 */