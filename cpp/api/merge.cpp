#include<iostream>
using namespace std;
#include<algorithm>
#include<vector>
#include<string>

class Person {
public:
    Person(string name, int age) :m_Name(name), m_Age(age) {}
    Person() :m_Name(" "), m_Age(0) {}
    string m_Name;
    int m_Age;
};

// 重载 << 输出对象
ostream &operator<<(ostream &cout, const Person &p) {
    cout << p.m_Name << " " << p.m_Age << endl;
    return cout;
}

// 输出内置和自定义数据容器元素模板
template<typename T>
void PrintVector(const T &x) {
    cout << x << " ";
}

// 内置数据类型合并
void test01() {
    vector<int>v1; // 有序
    vector<int>v2; // 有序
    //for (int i = 0; i < 10; i++) {
    //    v1.push_back(i); // 0 - 9
    //    v2.push_back(i); // 0 - 9
    //}
    v1.push_back(6);
    v1.push_back(5);
    v1.push_back(4);
    v1.push_back(3);

    v2.push_back(6);
    v2.push_back(5);
    v2.push_back(4);
    v2.push_back(3);


    vector<int>v_target; // 目标容器

    v_target.resize(v1.size() + v2.size()); // 目标容器需要给定大小

    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v_target.begin());// 合并

    for_each(v_target.begin(), v_target.end(), PrintVector<int>); // 遍历目标容器
    cout << endl;
}

// 排序仿函数
class my_sort {
public:
    bool operator()(const Person &p1, const Person &p2) {
        return (p1.m_Age < p2.m_Age);
    }
};

// 自定义数据类型合并
void test02() {
    vector<Person>v1; // 有序
    vector<Person>v2; // 有序
    Person p1("李四", 19);
    Person p2("王五", 18);
    Person p3("张三", 20);

    v1.push_back(p1);
    v1.push_back(p2);
    v1.push_back(p3);

    v2.push_back(p1);
    v2.push_back(p2);
    v2.push_back(p3);

    sort(v1.begin(), v1.end(), my_sort());
    sort(v2.begin(), v2.end(), my_sort());

    vector<Person> v_target; // 目标容器
    v_target.resize(v1.size() + v2.size()); // 目标容器给定大小

    // 合并，这个里面也要传入排序方法仿函数
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v_target.begin(), my_sort());

    for_each(v_target.begin(), v_target.end(), PrintVector<Person>); // 遍历
}

int main() {
    test01();
    test02();
    return 0;
}