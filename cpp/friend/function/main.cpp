#include <iostream>

class A
{
public:
    int get_a()
    {
        return m_a;
    }

private:
    friend void set_A_a(A &a) // friend 不受访问限制符影响
    {
        a.m_a = 10;
    }
    int m_a;
};

class B
{
public:
    int get_b()
    {
        return m_b;
    }

private:
    friend void set_B_b(B &); // friend 不受访问限制符影响
    int m_b;
};

void set_B_b(B &b)
{
    b.m_b = 10;
}

int main(int argc, char *argv[])
{
    A a;
    set_A_a(a);
    std::cout << a.get_a() << std::endl;

    B b;
    set_B_b(b);
    std::cout << b.get_b() << std::endl;
    return 0;
}