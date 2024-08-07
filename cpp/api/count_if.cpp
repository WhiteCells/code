#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

class Person {
public:
    Person(string name, int age) : m_Name(name), m_Age(age) {}
    string m_Name;
    int m_Age;
};

class Person_find {
public:
    bool operator()(const Person &p) {
        return p.m_Age > 18;
    }
};

class my_find {
public:
    bool operator()(const int &x) {
        return x > 2 && x < 5;
    }
};

void test01() {
    vector<int> v { 1, 2, 3, 4, 5, 6 };
    cout << count_if(v.begin(), v.end(), my_find()) << endl;
}

void test02() {
    vector<Person> v {
        { "lll", 17 },
        { "222", 18 },
        { "333", 19 },
        { "444", 19 },
    };
    cout << count_if(v.begin(), v.end(), Person_find()) << endl;
    cout << count_if(v.begin(), v.end(), [&v](const Person &p) {return p.m_Age > 18;}) << endl;
}

int main() {
    test01();
    test02();
    return 0;
}