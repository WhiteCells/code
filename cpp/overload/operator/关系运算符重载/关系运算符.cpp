#include<iostream>
#include<string>
using namespace std;

class Person {
public:
    Person(string name, int age)
    {
        m_Name = name;
        m_Age = age;
    }
    bool operator==(Person &p) {
        if ((this->m_Name == p.m_Name) && (this->m_Age == p.m_Age)) {
            return true;
        } else {
            return false;
        }
    }
    bool operator!=(Person &p) {
        if ((this->m_Name == p.m_Name) && (this->m_Age == p.m_Age)) {
            return false;
        } else {
            return true;
        }
    }
    string m_Name;
    int m_Age;
};