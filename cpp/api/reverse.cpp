#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

class Person {
public:
    Person(string name, int age) :m_Name(name), m_Age(age) {}
    string m_Name;
    int m_Age;
};

// 重载 << 输出对象
ostream& operator<<(ostream& cout, const Person& p) {
    cout << p.m_Name << " " << p.m_Age << endl;
    return cout;
}

// 输出 vector 模板函数
template<typename T>
void PrintVector(const T& x) {
    cout << x;
}

// 反转内置数据类型容器
void test01() {
    vector<int>v;
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }
    cout << "——反转前——" << endl;
    for_each(v.begin(), v.end(), PrintVector<int>);
    cout << endl;

    cout << "——反转后——" << endl;
    reverse(v.begin(), v.end());
    for_each(v.begin(), v.end(), PrintVector<int>);
    cout << endl;
}

// 反转自定义数据类型容器
void test02() {
    vector<Person>v;
    Person p1("张三", 18);
    Person p2("李四", 19);
    Person p3("王五", 20);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);

    cout << "——反转前——" << endl;
    for_each(v.begin(), v.end(), PrintVector<Person>);
    
    cout << "——反转后——" << endl;
    reverse(v.begin(), v.end());
    for_each(v.begin(), v.end(), PrintVector<Person>);
}

int main() {
    test01();
    test02();
    return 0;
}