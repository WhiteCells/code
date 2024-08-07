#include<iostream>
using namespace std;

class Person
{
public:
    // 构造函数
    Person()
    {
        cout << "Person 无参构造函数调用" << endl;
        m_Age = 0;
    }
    // 构造函数重载
    Person(int age)
    {
        cout << "Person 有参构造函数调用" << endl;
        m_Age = age;
    }
    // 拷贝构造函数
    Person(const Person &p)
    {
        cout << "Person 拷贝构造函数调用" << endl;
        m_Age = p.m_Age;
    }
    // 析构函数
    ~Person()
    {
        cout << "Person 析构函数调用" << endl;
    }
    int m_Age;
};

// 拷贝构造函数调用时机

// 1、使用一个已经创建完毕的对象来初始化一个新对象
void test01()
{
    Person p1(20); // 调用有参构造函数
    Person p2(p1); // 调用拷贝构造函数

    cout << "p2 的年龄：" << p2.m_Age << endl;
}

// 2、值传递的方式给函数参数传值
void doWork(Person p) // 拷贝临时副本
{

}
void test02()
{
    Person p;
    doWork(p);
}

// 3、值方式返回局部变量
Person doWork2()
{
    Person p1;
    return p1; // 返回的是值
}
void test03()
{
    Person p = doWork2();
}

int main()
{
    test01();
    test02();
    test03();
    return 0;
}
