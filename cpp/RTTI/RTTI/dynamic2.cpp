#include <iostream>

class Base {
public:
    virtual ~Base() {}
};

class Derive : public Base {};

int main() {
    Base *base1 = new Base(); // base1 指向基类
    Derive *derive1 = dynamic_cast<Derive *>(base1); // 基类转换为派生类
    std::cout << derive1 << std::endl; // 0 转换失败

    Base *base2 = new Derive(); // base2 指向派生类
    Derive *derive2 = dynamic_cast<Derive *>(base2); // 派生类转换为基类
    std::cout << derive2 << std::endl; // 非 0 转换成功

    delete derive1;
    delete derive2;
    return 0;
}