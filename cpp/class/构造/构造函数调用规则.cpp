#include <iostream>
#include <string>

using namespace std;

class Person {
public:
    Person() {
        cout << "Person()" << endl;
    }

    Person(int &&a) {
        std::cout << "Person(int &&a)" << std::endl;
        this->age_ = a;
    }

    Person(int a) {
        std::cout << "Person(int a)" << std::endl;
        this->age_ = a;
    }

    Person(string name, int age) {
        cout << "Person(string name, int age)" << endl;
        this->name_ = name;
        this->age_ = age;
    }

    Person(const Person &p) {
        std::cout << "Person(const Person &p)" << std::endl;
        age_ = p.age_;
        name_ = p.name_;
    }

    string name_;
    int age_;
};

void test01() {
    Person p1("aaa", 20);

    Person p2(p1); // 拷贝
}

void test2() {
    int &&a1 = 1;
    Person p1(a1); // Person(int a)

    int a2 = 1;
    Person p2(a2); // Person(int a)

    int &a3 = a2;
    Person p3(a3); // Person(int a)
}

int main() {
    test01();
    // test2();
    return 0;
}