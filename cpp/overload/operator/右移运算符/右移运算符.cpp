#include <iostream>
#include <vector>
#include <string>

class Person {
public:
    Person() {}
    Person(std::string name, int age) : m_Name(name), m_Age(age) {}
    std::string m_Name;
    int m_Age;
};

std::istream &operator>>(std::istream &in, Person &p) {
    in >> p.m_Name >> p.m_Age;
    return in;
}

std::ostream &operator<<(std::ostream &os, const Person &p) {
    os << p.m_Name << " " << p.m_Age;
    return os;
}

void test() {
    Person p1;
    std::cin >> p1;
    std::cout << p1 << '\n';
}

int main() {
    test();
    return 0;
}