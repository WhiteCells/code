#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

class Person
{
public:
    Person(string name, int age) :
        m_Name(name), m_Age(age) {}
    string m_Name;
    int m_Age;
};

ostream &operator<<(ostream &os, const Person &p)
{
    os << p.m_Name << " " << p.m_Age << endl;
    return os;
}

template <typename T>
void PrintVector(const T &x)
{
    cout << x;
}

void test01()
{
    vector<int> v {10, 20, 30};
    int n = v.size();
    v.resize(10);
    // 后期填充
    fill(v.begin() + n, v.end(), 50);
    for_each(v.begin(), v.end(), PrintVector<int>);
    cout << endl;
}

// 自定义数据类型
void test02()
{
    vector<Person> v;
    Person p1("A", 19);
    Person p2("B", 20);
    Person p3("C", 17);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);

    Person fill_p("D", 100);
    fill(v.begin(), v.end(), fill_p);
    for_each(v.begin(), v.end(), PrintVector<Person>);
}

int main()
{
    test01();
    test02();
    return 0;
}