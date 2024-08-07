#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

class Person {
public:
    Person(string name, int age) :m_Name(name), m_Age(age) {}
    Person() {}
    string m_Name;
    int m_Age;
};

class my_Transform {
public:
    Person operator()(const Person& p) {
        return p; // 默认构造要在
    }
};

Person my_Transform2(const Person& p) {
    return p;
}

void PrintVector(const vector<Person>& pv) {
    for (vector<Person>::const_iterator it = pv.begin(); it != pv.end(); ++it) {
        cout << (*it).m_Name << " " << it->m_Age << endl;
    }
}

void test() {
    vector<Person>v1;
    Person p1("李四", 19);
    Person p2("张三", 20);
    Person p3("王五", 18);

    v1.push_back(p1);
    v1.push_back(p2);
    v1.push_back(p3);

    PrintVector(v1);

    vector<Person>v2;
    v2.resize(v1.size());

    transform(v1.begin(), v1.end(), v2.begin(), my_Transform());

    PrintVector(v2);
    v1.push_back(p1);
    v2.resize(v1.size());
    transform(v1.begin(), v1.end(), v2.begin(), my_Transform2);

    PrintVector(v2);
}

int main() {
    test();
    return 0;
}