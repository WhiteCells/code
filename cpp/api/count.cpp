#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void test01() {
    vector<int>v { 1, 2, 3, 4, 5, 1, 2, 1 };
    cout << count(v.begin(), v.end(), 1) << endl;
}

void test02() {
    class Person {
    public:
        Person(string name, int age) :m_Name(name), m_Age(age) {}
        bool operator==(const Person &p) {
            return this->m_Name == p.m_Name && this->m_Age == p.m_Age;
        }
        string m_Name;
        int m_Age;
    };
    vector<Person> v {
        Person("111", 16),
        Person("222", 17),
        Person("333", 13),
        Person("444", 11),
        Person("555", 15),
        Person("222", 17)
    };
    cout << count(v.begin(), v.end(), Person{"222", 17}) << endl;
}

int main() {
    test01();
    test02();
    return 0;
}