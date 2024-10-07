#include <string_view>
#include <iostream>

std::string_view get_view()
{
    return std::string_view("test");
}

int main(int argc, char *argv[])
{
    std::cout << get_view() << std::endl;

    std::string str = "test";
    std::string_view sv {str};
    std::cout << sv << std::endl;
    return 0;
}