#include<iostream>
#include<ctime>
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

ostream& operator<<(ostream& cout, const Person& p) {
    cout << p.m_Name << " " << p.m_Age << endl;
    return cout;
}

template<typename T>
void PrintVector(const T& x) {
    cout << x;
}

// 内置数据类型洗牌
void test01() {
    vector<int>v;
    for (int i = 0; i < 10; ++i) { v.push_back(i); }
    for_each(v.begin(), v.end(), PrintVector<int>);
    cout << endl;

    // 随机排序
    random_shuffle(v.begin(), v.end());
    for_each(v.begin(), v.end(), PrintVector<int>);
    cout << endl;
}

// 自定数据类型洗牌
void test02() {
    vector<Person>v;
    Person p1("李四", 16);
    Person p2("王五", 17);
    Person p3("李华", 18);
    Person p4("张三", 19);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    for_each(v.begin(), v.end(), PrintVector<Person>);
    cout << endl;

    // 随机排序
    random_shuffle(v.begin(), v.end());
    for_each(v.begin(), v.end(), PrintVector<Person>);
    cout << endl;
}

int main() {
    srand((unsigned)time(NULL));
    test01();
    test02();
    return 0;
}