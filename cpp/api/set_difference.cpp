#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

class Person {
public:
    Person(string name, int age) :m_Name(name), m_Age(age) {}
    Person() {}
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

// 内置数据类型差集
void test01() {
    vector<int>v1; // 有序
    vector<int>v2; // 有序

    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);

    v2.push_back(30);
    v2.push_back(40);
    v2.push_back(50);
    v2.push_back(60);

    cout << "v1 与 v2 的差集：";
    vector<int>v_target1; // 目标容器
    v_target1.resize(max(v1.size(), v2.size())); // 容器大小
    vector<int>::iterator EndIt1 = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v_target1.begin());
    for_each(v_target1.begin(), EndIt1, PrintVector<int>);
    cout << endl;
    
    cout << "v1 与 v2 的差集：";
    vector<int>v_target2; // 目标容器
    v_target2.resize(max(v1.size(), v2.size())); // 容器大小
    vector<int>::iterator EndIt2 = set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), v_target2.begin());
    for_each(v_target2.begin(), EndIt2, PrintVector<int>);
    cout << endl;
}

// 年龄排序仿函数
class Person_sort {
public:
    bool operator()(const Person& p1, const Person& p2) {
        return (p1.m_Age < p2.m_Age); // m_Age 降序
    }
};

// 自定义数据类型差集
void test02() {
    vector<Person>v1; // 有序
    vector<Person>v2; // 有序

    Person p1("A", 22);
    Person p2("B", 21);
    Person p3("C", 20);
    Person p4("D", 19);
    Person p5("E", 18);

    v1.push_back(p1);
    v1.push_back(p2);
    v1.push_back(p3);

    v2.push_back(p3);
    v2.push_back(p4);
    v2.push_back(p5);

    sort(v1.begin(), v1.end(), Person_sort()); // 排序
    sort(v2.begin(), v2.end(), Person_sort()); // 排序

    cout << "v1 和 v2 的差集：" << endl;
    vector<Person>v_target1;
    v_target1.resize(max(v1.size(), v2.size()));
    vector<Person>::iterator EndIt1 = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v_target1.begin(), Person_sort());
    for_each(v_target1.begin(), EndIt1, PrintVector<Person>);
    cout << endl;

    cout << "v2 与 v1 的差集：" << endl;;
    vector<Person>v_target2;
    v_target2.resize(max(v1.size(), v2.size()));
    vector<Person>::iterator EndIt2 = set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), v_target2.begin(), Person_sort());
    for_each(v_target2.begin(), EndIt2, PrintVector<Person>);
    cout << endl;
}

int main() {
    test01();
    test02();
    system("pause");
    return 0;
}