#include <iostream>

class A
{
private:
    friend class B; // friend 不受访问限制符影响
    int m_a {10};
};

class B
{
public:
    int get_A_a(A &&a)
    {
        return a.m_a;
    }

    void set_a(int val)
    {
        a.m_a = val;
    }

    void print_a()
    {
        std::cout << a.m_a << std::endl;
    }

private:
    A a;
};

int main(int argc, char *argv[])
{
    std::cout << B().get_A_a(A()) << std::endl;

    B b;
    b.set_a(20);
    b.print_a();
    return 0;
}