#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class Person {
public:
    Person(string name, int age) : m_Name(name), m_Age(age) {}
    string m_Name;
    int m_Age;
};

// 内置数据类型排序
void test01() {
    auto print = [&](vector<int> &v) {
        for (const auto &ele : v) { cout << ele << ' '; }
        cout << endl;
    };
    vector<int> v;
    for (int i = 10; i > 0; --i) { v.push_back(i); }

    sort(v.begin(), v.end());
    print(v);

    class MySort {
    public:
        bool operator()(int &value1, int &value2) {
            return (value1 > value2);
        }
    };

    sort(v.begin(), v.end(), MySort());
    print(v);
}

// 自定义数据类型排序
void test02() {
    auto print = [&](vector<Person> &v) {
        for (const auto &p : v) { cout << p.m_Name << " " << p.m_Age << endl; }
        cout << endl;
    };

    vector<Person> v { Person("aa", 19), Person("bb", 18), Person("cc", 20), Person("aa", 17) };

    class MySort {
    public:
        bool operator()(const Person &p1, const Person &p2) {
            return (p1.m_Age < p2.m_Age);
        }
    };

    sort(v.begin(), v.end(), MySort());
    print(v);
}

int main() {
    test01();
    test02();
    return 0;
}