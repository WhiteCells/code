#include<iostream>
using namespace std;

class Person {
public:
    Person() {
        cout << "Person()" << endl;
    }
    Person(int age, int height) {
        Age = age;
        Height = new int(height);
        cout << "Person(int age, int height)" << endl;
    }
    Person(const Person& p) {
        Age = p.Age;
        // Height = p.Height; // 编译器默认实现
        // 深拷贝
        Height = new int(*p.Height); // 自己实现
    }
    ~Person() {
        // 析构操作
        // 将堆区开辟的数据释放
        if (Height != NULL) {
            delete(Height); // 释放指针
            Height = NULL;  // 指针置空
        }  
        cout << "Person 析构函数调用"     << endl;
    }
    int Age;
    int* Height; // 身高指针变量
};

void test01(){
    Person p1(18, 180);
    cout << "p1 的年龄：" <<  p1.Age    << endl;
    cout << "p1 的身高：" << *p1.Height << endl;
    Person p2(p1); 
    cout << "p2 的年龄：" <<  p2.Age    << endl;
    cout << "p2 的身高：" << *p2.Height << endl;
}

int main(){
    test01();
    return 0;
}