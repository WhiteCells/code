#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

class Person {
public:
    Person(string name, int age) :m_Name(name), m_Age(age) {}
    // 重载 ==，replace 底层代码需要对比
    bool operator==(const Person& p) {
        return (p.m_Name == this->m_Name && p.m_Age == this->m_Age);
    }
    string m_Name;
    int m_Age;
};

// 重载 <<
ostream& operator<<(ostream& cout, const Person& p) {
    cout << p.m_Name << " " << p.m_Age << endl;
    return cout;
}

template<typename T>
void PrintVector(const T& x) {
    cout << x << " ";
}

// 内置数据类型替换
void test01() {
    vector<int>v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(30);
    v.push_back(40);

    cout << "——替换前——" << endl;
    for_each(v.begin(), v.end(), PrintVector<int>); // 遍历
    cout << endl;

    cout << "——替换后——" << endl;
    replace(v.begin(), v.end(), 30, 20); // 替换
    for_each(v.begin(), v.end(), PrintVector<int>);  // 遍历
    cout << endl;
}

// 自定义数据类型替换
void test02() {
    vector<Person>v;
    Person p1("A", 16);
    Person p2("B", 17);
    Person p3("D", 19);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);

    cout << "——替换前——" << endl;
    for_each(v.begin(), v.end(), PrintVector<Person>); // 遍历

    cout << "——替换后——" << endl;
    Person p4("C", 18);
    replace(v.begin(), v.end(), p3, p4); // 替换
    for_each(v.begin(), v.end(), PrintVector<Person>); // 遍历
}

int main() {
    test01();
    test02();
    return 0;
}