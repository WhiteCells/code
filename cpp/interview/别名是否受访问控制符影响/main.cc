#include <iostream>

class C
{
    typedef long long ll1;
    using ui1 = unsigned int;

public:
    typedef long long ll2;
    using ui2 = unsigned int;

protected:
    typedef long long ll3;
    using ui3 = unsigned int;
};

class D : C
{
    // ll1 a = 1; // error
    // ui1 c = 1; // error
    ll2 b = 1;
    ui2 c = 1;
    ll3 e = 1;
    ui3 f = 1;

public:
    D()
    {
        std::cout << e << f << std::endl;
    }
};

int main(int argc, char *argv[])
{
    D{};
}