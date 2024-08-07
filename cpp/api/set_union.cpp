#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

void test01() {
    vector<int> v1 { 3, 4, 5, 6 };
    vector<int> v2 { 5, 6, 7 };
    sort(v1.begin(), v1.begin());
    sort(v2.begin(), v2.begin());
    vector<int> v_target;
    v_target.resize(v1.size() + v2.size());
    vector<int>::iterator end_it = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v_target.begin());
    for (auto it = v_target.begin(); it != end_it; ++it) {
        cout << *it << " ";
    }
    cout << '\n';
}

void test02() {
    class Person {
    public:
        Person() {}
        Person(string name, int age) : m_Name(name), m_Age(age) {}
        string m_Name;
        int m_Age;
    };

    class PersonComp {
    public:
        bool operator()(const Person &p1, const Person &p2) {
            return p1.m_Age == p2.m_Age && p1.m_Name == p2.m_Name;
        }
    };
    vector<Person>v1 {
        Person("A", 17),
        Person("B", 19),
        Person("C", 21),
        Person("D", 23),
        Person("E", 25)
    };
    vector<Person> v2 {
        Person("B", 19),
        Person("C", 22),
        Person("D", 23),
    };
    vector<Person>v_target;
    v_target.resize(v1.size() + v2.size());
    vector<Person>::iterator end_it = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v_target.begin(), PersonComp());
    for (auto it = v_target.begin(); it != end_it; ++it) {
        cout << it->m_Name << " " << it->m_Age << '\n';
    }
    cout << '\n';
}

int main() {
    test01();
    test02();
    return 0;
}