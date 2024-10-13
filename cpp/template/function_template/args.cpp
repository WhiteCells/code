#include <iostream>

template <typename... Args>
void print(Args... args)
{
    int _[] {(std::cout << args << " ", 0)...};
}

int main(int argc, char *argv[])
{
    print(1, 2.2, "hello");
    return 0;
}