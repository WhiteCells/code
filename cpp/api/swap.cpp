#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

class Person {
public:
    Person(string name, int age) :m_Name(name), m_Age(age) {}
    string m_Name;
    int m_Age;
};

ostream& operator<<(ostream& cout, const Person& p) {
    cout << p.m_Name << " " << p.m_Age << endl;
    return cout;
}

template<typename T>
void PrintVector(const T& x) {
    cout << x << " ";
}

// 内置数据类型交换
void test01() {
    vector<int>v1;
    vector<int>v2;
    for (int i = 0; i < 10; ++i) {
        v1.push_back(i);
    }
    for (int i = 10; i > 0; --i) {
        v2.push_back(i);
    }
    cout << "——交换前——" << endl;
    cout << "v1:";
    for_each(v1.begin(), v1.end(), PrintVector<int>);
    cout << endl;
    cout << "v2:";
    for_each(v2.begin(), v2.end(), PrintVector<int>);
    cout << endl;

    cout << "——交换后——" << endl;
    swap(v1, v2);
    cout << "v1:";
    for_each(v1.begin(), v1.end(), PrintVector<int>);
    cout << endl;
    cout << "v2:";
    for_each(v2.begin(), v2.end(), PrintVector<int>);
    cout << endl;
}

// 自定义数据类型交换
void test02() {
    vector<Person>v1;
    Person p1("A", 19);
    Person p2("B", 20);
    Person p3("C", 21);
    v1.push_back(p1);
    v1.push_back(p2);
    v1.push_back(p3);

    vector<Person>v2;
    Person p4("D", 22);
    Person p5("E", 23);
    Person p6("F", 24);
    Person p7("G", 25);
    v2.push_back(p4);
    v2.push_back(p5);
    v2.push_back(p6);
    v2.push_back(p7);

    cout << "——交换前——" << endl;
    cout << "v1: " << endl;
    for_each(v1.begin(), v1.end(), PrintVector<Person>);
    cout << "v2: " << endl;
    for_each(v2.begin(), v2.end(), PrintVector<Person>);

    cout << "——交换后——" << endl;
    swap(v1, v2);
    cout << "v1: " << endl;
    for_each(v1.begin(), v1.end(), PrintVector<Person>);
    cout << "v2: " << endl;
    for_each(v2.begin(), v2.end(), PrintVector<Person>);
}

int main() {
    test01();
    test02();
    return 0;
}