// #include <iostream>
// 
// using namespace std;
// 
// void test01() {
//     // c++11 使用 make_pair 初始化
//     pair<int, bool> pr1 = make_pair<int, bool>(1, false); // make_pair 是一个模板函数
//     pair<int, bool> pr2 = make_pair(2, false); // 省略模板参数, 自动推导 pair 类型
// 
//     cout << pr1.first << pr1.second << endl;
//     cout << pr2.first << pr2.second << endl;
// 
//     // 使用 pair<int, bool> 类型转换
//     pair<int, bool> pr3 = pair<int, bool>(3, false);
//     pair<int, bool> pr4 = pair<int, bool> { 4, false }; // 聚合初始化
//     pair<int, bool> pr5 = pair { 5, false }; // c++11 编译器会根据大括号中的元素类型自动推导出模板参数
// 
//     // c++17 通过结构化绑定的方式直接将 pair 对象的元素绑定到变量中
//     auto [x, y] = pair { 6, false };
//     
//     cout << pr3.first << pr3.second << endl;
//     cout << pr4.first << pr4.second << endl;
//     cout << pr5.first << pr5.second << endl;
//     cout << x << y << endl;
// }
// 
// int main() {
//     test01();
//     return 0;
// }

#include <iostream>
#include <vector>

void foo() {
    std::pair<int, int> p1 = std::make_pair<int, int>(1, 2);
    auto p2 = std::make_pair<int>(1, 2);
    auto p3 = std::make_pair(1, 1.1);
    auto p4 = std::pair<int, int>({1, 2});
    auto p5 = std::pair<int, int> { 1, 2 };
    auto p6 = std::pair<int, int>(1, 2);
    // auto p7 = std::pair(1, 2.2); // C++11
    auto p7 = std::pair<int, int>(1, 2.2);
}

int main() {
    foo();
    return 0;
}