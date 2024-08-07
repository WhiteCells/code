#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<algorithm>

class Person {
public:
    Person(string name, int age) :m_Name(name), m_Age(age) {}   
    string m_Name;
    int m_Age;
};

class Greater5 {
public:
    bool operator()(const int& x) {
        if (x > 5) return true;
        else return false;
    }
};

class Greater20 {
public:
    bool operator()(const Person& p) {
        if (p.m_Age > 20) return true;
        else return false;
    }
};

bool Greater8(const int& x) {
    if (x > 8) return true;
    else return false;
}

bool Greater30(const Person& p) {
    if (p.m_Age > 30) return true;
    else return false;
}

// 内置数据类型 find_if
void test01() {
    vector<int>v;
    for (int i = 0; i < 10; ++i)  v.push_back(i + 1);

    vector<int>::iterator it1 = find_if(v.begin(), v.end(), Greater5()); // 传入仿函数（谓词）
    vector<int>::iterator it2 = find_if(v.begin(), v.end(), Greater8);   // 传入普通函数

    if (it1 != v.end()) {
        cout << "find it " << *it1 << endl;
    }
    else {
        cout << "no find it" << endl;
    }
    if (it2 != v.end()) {
        cout << "find it " << *it2 << endl;
    }
    else {
        cout << "no find it" << endl;
    }
}

// 自定义数据类型 find_if
void test02() {
    vector<Person>v;

    Person p1("张三", 18);
    Person p2("张三", 30);
    Person p3("李四", 19);
    Person p4("王五", 40);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    vector<Person>::iterator it1 = find_if(v.begin(), v.end(), Greater20()); // 传入仿函数（谓词）
    vector<Person>::iterator it2 = find_if(v.begin(), v.end(), Greater30);   // 传入普通函数

    if (it1 != v.end()) {
        cout << "找到了" << it1->m_Name << " " << (*it1).m_Age << endl;
    }
    else {
        cout << "未找到" << endl;
    }
    if (it2 != v.end()) {
        cout << "找到了" << it2->m_Name << " " << (*it2).m_Age << endl;
    }
    else {
        cout << "未找到" << endl;
    }
}

int main() {
    test01();
    test02();
    system("pause");
    return 0;
}