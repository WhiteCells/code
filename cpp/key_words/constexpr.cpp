/*
    constexpr 和 const 都用于声明常量，但在具体使用和语义上存在一些区别。

    使用场景：
        const：const 修饰的变量可以是运行时或编译时常量。可以用于修饰变量、函数参数、函数返回值以及类成员变量。
        constexpr：constexpr 修饰的对象必须在编译时求值得到常量表达式。主要用于修饰变量、函数和类成员函数。

    求值时机：
        const：const 变量的值可以在运行时确定，其初始化可以在运行时进行。
        constexpr：constexpr 对象的值必须在编译时确定，并且只能使用常量表达式进行初始化。编译器会在编译期间计算并替换使用该常量的地方。

    编译时优化：
        const：const 变量在运行时被读取，编译器无法在编译时对其进行优化。
        constexpr：constexpr 对象在编译时被求值，编译器可以对其进行优化，避免运行时开销。

    类型：
        const：const 可以修饰不同类型的对象，包括基本类型、自定义类型、指针等。
        constexpr：constexpr 主要用于修饰常量表达式，可以修饰基本类型、自定义类型和指针，但有一些限制，例如函数体内只能包含简单的语句。

    需要注意的是，constexpr 的使用比 const 更为严格，因为编译器要求对 constexpr 对象进行编译时求值。此外，constexpr 还提供了更强的类型检查和编译时优化能力。
 */

#include <iostream>

/* constexpr 修饰类成员变量、类成员函数 */
class A {
private:
    // 要让一个静态数据成员成为一个可用于编译时常量求值的常量表达式，它必须是一个静态成员（static）。
    // 在类中声明的静态成员变量只有一份拷贝，无论创建多少个类的对象，所有的对象都共享同一个静态成员变量。这意味着静态成员变量存在于类本身而不是对象实例中。
    // 而对于非静态成员，每个类的对象都会拥有独立的拷贝，而不是共享一个值。因此，非静态成员变量在编译时无法确定其具体的值，所以无法作为一个编译时常量使用。
    constexpr static int a = 10;
    constexpr static int b = 20;
    int c = 30;
public:
    // 用 constexpr 关键字来声明成员函数 GetAmultB() 是为了指示编译器该函数可以在编译时进行求值，并且返回的结果也是一个编译时常量。
    constexpr int GetAmultB() const {
        return a * b;
    } // 函数返回一个编译时常量
};

/*
    根据 C++ 标准规定，在编译时初始化 constexpr 变量时，其初始值必须是一个编译时常量表达式。
    而 a.GetAmultB() 是一个在运行时求值的函数调用，不能作为编译时常量使用
 */
void TestAC1() {
    A a;
    int ret = a.GetAmultB();
    std::cout << ret << '\n';
}

/* constexpr 修饰全局变量 */
constexpr int a = 20;
void TestGVal() {
    std::cout << a << '\n';
}

constexpr int c = 10, d = 20;
#define M 100 // 宏是预处理时进行文本替换，不被视为编译时常量
/* constexpr 修饰函数，函数体内使用的变量必须是在编译时常量 */
constexpr int GFunc() {
    return c + d + M;
}

void TestGFunc() {
    std::cout << GFunc() << '\n';
}

int main() {
    // TestAC1();
    // TestAC2();
    // TestGVal();
    TestGFunc();
    return 0;
}