#include <concepts>
#include <algorithm>
#include <stack>
#include <vector>
#include <iostream>
#include <string>

// 定义可排序容器的概念
template <typename C>
concept SortableContainer = requires(C c) {
    { c.begin() } -> std::input_iterator;
    { c.end() } -> std::input_iterator;
    { *c.begin() < *c.begin() } -> std::convertible_to<bool>;
};

// 通用的排序算法
template <SortableContainer C>
void sort_and_print(C &container)
{
    std::sort(container.begin(), container.end());
    for (const auto &item : container) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

// 自定义类型如果实现了<运算符也能工作
struct Point
{
    int x, y;
    bool operator<(const Point &other) const
    {
        return x < other.x || (x == other.x && y < other.y);
    }
};
std::ostream &operator<<(std::ostream &os, const Point &p)
{
    return os << "(" << p.x << "," << p.y << ")";
}

int main()
{
    // 测试
    std::vector<int> nums {3, 1, 4, 1, 5};
    sort_and_print(nums);
    // OK

    std::vector<std::string> words {"hello", "world"};
    sort_and_print(words);
    // OK

    std::vector<Point> points;
    sort_and_print(points);
    // OK，如果Point实现了<

    // std::stack<int> stk;
    // stk.push(3);
    // stk.push(2);
    // sort_and_print(stk);
}