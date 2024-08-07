#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

void test01() {
    vector<int>v;
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }
    vector<int>v_target;
    v_target.resize(v.size());
    copy(v.begin(), v.end(), v_target.begin());
}

void test02() {
    class Person {
    public:
        Person(string name, int age) :m_Name(name), m_Age(age) {}
        Person() {}
        string m_Name;
        int m_Age;
    };
    vector<Person>v {
        Person("111", 18),
        Person("222", 19),
        Person("333", 20)
    };
    vector<Person>v_target;
    v_target.resize(v.size());
    copy(v.begin(), v.end(), v_target.begin());
}

int main() {
    test01();
    test02();
    return 0;
}