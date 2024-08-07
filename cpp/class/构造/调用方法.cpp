#include <iostream>
#include <string>

class Person {
public:
    Person() {
        std::cout << "Person 无参构造函数调用" << std::endl;
    }

    Person(int a) {
        age = a;
        std::cout << "Person 有参构造函数调用" << std::endl;
    }

    Person(const Person &p) {
        age = p.age;
        std::cout << "Person 拷贝构造函数调用" << std::endl;
    }

    ~Person() {
        std::cout << "Person 析构函数调用" << std::endl;
    }
private:
    std::string name;
    std::string sex;
    int age;
};

// 括号法
void foo1() {
    Person p1; // 无参构造
    // Person p4(); // ERROR 这是一个函数声明
    Person p2(10); // 有参构造
    Person p3(p2); // 拷贝构造
}

// 显式调用
void foo2() {
    Person p1 = Person(1);
    Person p2 = Person(p1);
}

// 隐式转换，单参数
void foo3() {
    Person p1 = 10;
}

// 匿名对象
void foo4() {
    Person(10); // 匿名对象在创建后会立即被销毁
    std::cout << "---" << std::endl;

    // 不要使用拷贝构造函数初始化匿名对象，导致未定义的行为
    // Person p1 = 1;
    // Person(p1);
}

int main() {
    // foo1();
    foo4();
    return 0;
}