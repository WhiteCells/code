#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Person
{
public:
    Person(string name, int age) :
        m_Name(name), m_Age(age) {}
    // 重载 == 让底层 find 知道 == 方式
    bool operator==(const Person &p)
    {
        if (this->m_Name == p.m_Name && this->m_Age == p.m_Age)
            return true;
        else
            return false;
    }
    string m_Name;
    int m_Age;
};

// 查找内置数据类型
void test1()
{
    vector<int> v;
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }
    int find_x = 9;
    vector<int>::iterator it = find(v.begin(), v.end(), find_x);
    if (it != v.end()) {
        cout << "找到了" << *it << endl;
    }
    else {
        cout << "未找到" << endl;
    }
}

// 查找自定义数据类型
void test2()
{
    vector<Person> v;
    Person p1("李四", 19);
    Person p2("张三", 19);
    Person p3("王五", 19);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);

    Person find_p("张三", 19);
    vector<Person>::iterator it = find(v.begin(), v.end(), find_p);
    if (it != v.end()) {
        cout << "找到" << (*it).m_Name << " " << it->m_Age << endl;
    }
    else {
        cout << "未找到" << endl;
    }
}

int main()
{
    test1();
    test2();
    return 0;
}