#include <thread>
#include <mutex>
#include <iostream>

class A
{
public:
    A(int a) :
        a_(a) {}
    A(const A &other)
    {
        a_ = other.a_;
    }

    int getA()
    {
        std::lock_guard<std::mutex> lock(mtx_);
        return a_;
    }

    void setA(int a)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        a_ = a;
    }

    friend void swap(A &lhs, A &rhs)
    {
        if (&lhs == &rhs) {
            return;
        }
        std::lock(lhs.mtx_, rhs.mtx_);
        std::lock_guard<std::mutex> lock_a(lhs.mtx_, std::adopt_lock);
        std::lock_guard<std::mutex> lock_b(rhs.mtx_, std::adopt_lock);
        std::swap(lhs.a_, rhs.a_);
    }

private:
    int a_;
    std::mutex mtx_;
};

class X
{
public:
    X() :
        a_(1)
    {
    }

    friend void swap(X &lhs, X &rhs)
    {
        if (&lhs == &rhs) {
            return;
        }
        std::lock(lhs.mtx_, rhs.mtx_);
        std::lock_guard<std::mutex> lock_a(lhs.mtx_, std::adopt_lock);
        std::lock_guard<std::mutex> lock_b(rhs.mtx_, std::adopt_lock);
        swap(lhs.a_, rhs.a_);
    }

private:
    A a_;
    std::mutex mtx_;
};

int main(int argc, char *argv[])
{
    X x1;
    X x2;
    swap(x1, x2);

    A a1 {1};
    A a2 {2};
    swap(a1, a2);
    return 0;
}