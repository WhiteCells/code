#include <iostream>
#include <functional>

int main(int argc, char *argv[]) {

    // error
    // auto factorial = [](int n) {
    //     return n >= 1 ? n * factorial(n - 1) : 1;
    // };

    /**
     * 如果 lambda 中存在递归行为，则需要显式定义函数类型 `std::function<int(int)>`，
     * 并指明返回类型，同时使用捕获列表 `[&factorial]`  捕获 `factorial` 本身，
     * 才能使 `lambda` 可以在其主体中递归调用自己。（确保编译器知道 lambda 表达式的完整类型信息）
     */
    std::function<int(int)> factorial = [&factorial](int n) -> int {
        return n >= 1 ? n * factorial(n - 1) : 1;
    };

    std::cout << factorial(5) << std::endl;

    return 0;
}