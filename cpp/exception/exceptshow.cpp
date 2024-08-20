#include<iostream>

/*
C++11 标准已经弃用了异常规范，并在 C++17 标准中将其移除。主要原因如下：

难以维护： 随着代码的演化，维护异常规范变得越来越困难。
运行时开销： 编译器需要生成额外的代码来检查异常规范，这会增加运行时开销。
难以与模板和虚函数配合使用： 异常规范在模板和虚函数的使用中存在一些问题。


noexcept 关键字： C++11 引入了 noexcept 关键字，用于声明一个函数不会抛出任何异常。
文档和注释： 使用文档和注释来描述函数可能抛出的异常类型。

 */

// 只允许抛出 int，float，char 三种类型异常
void foo1() throw(int, float, char) {}

// 空异常规范表示函数可以抛出任何类型的异常
void foo2() throw() {
    try {
        throw std::runtime_error("runtime error");
    } catch (...) {
        std::cout << "except" << std::endl;
    }
}

// 允许抛出任何异常
void foo3() {}

// 不允许抛出任何异常
void foo3() noexcept {
// void foo4() noexcept(true) {
    throw std::runtime_error("runtime error");
}

// 允许抛出任何异常
void foo5() noexcept(false) {
    throw std::runtime_error("runtime error");
}

int main(int argc, char *argv[]) {
    try {
        foo3();
    } catch (const std::exception &e) {
        std::cout << "exception: " << e.what() << std::endl;
    }
    return 0;
}