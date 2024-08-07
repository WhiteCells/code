#include<iostream>
#include<string>
using namespace std;

class Person
{
public:
    Person(string name, int age)
    {
        m_Name = name;
        m_Age = age;
    }
    bool operator==(Person& p)
    {
        if ((this->m_Name == p.m_Name) && (this->m_Age == p.m_Age))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool operator!=(Person& p)
    {
        if ((this->m_Name == p.m_Name) && (this->m_Age == p.m_Age))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    string m_Name;
    int m_Age;
};

void test1()
{
    Person p1("�", 18);
    Person p2("�1", 18);
    
    // ��ıȽ�
    if (p1 == p2)
    {
        cout << "p1 �� p2 ���" << endl;
    }
    else
    {
        cout << "p1 �� p2 �����" << endl;
    }
    if (p1 != p2)
    {
        cout << "p1 �� p2 �����" << endl;
    }
    else
    {
        cout << "p1 �� p2 ���" << endl;
    }
}
int main()
{
    test1();
    system("pause");
    return 0;
}