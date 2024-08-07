#include<iostream>
using namespace std;

class Person {
public:
    void showClassName() {
        cout << __func__ << endl;
    }
    void showPersonAge() {
        if (!this) { // redundancy
            return;
        }
        cout << "age = " << this->m_Age << endl;
    }
    int m_Age;
};

void test01() {
    Person *p = nullptr;
    if (p) { // essential
        p->showClassName();
        p->showPersonAge();
    }
}

int main() {
    test01();
    return 0;
}