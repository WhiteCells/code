#include <iostream>
#include <vector>
#include <functional>

#include <set>

auto print = [&](const auto& s) {
    for (const auto& ele : s) {
        std::cout << ele << ' ';
    }
    std::cout << '\n';
};

// set api
void UsedSet() {
    std::set<int> s { 0, 8, 7, 6, 5, 4, 3, 2, 1 };

    // for (std::set<int>::iterator it = s.begin(); it != s.end(); ++it) { // 迭代器遍历
    //     std::cout << *it << " ";
    // }
    // std::cout << '\n';
    for (std::set<int>::const_iterator it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << '\n';

    std::cout << "*s.begin() = " << *s.begin() << '\n';   // 返回集合最小值
    std::cout << "*s.rbegin() = " << *s.rbegin() << '\n'; // 返回集合最大值

    // s.end() 指向最后一个元素的下一个位置的迭代器
    std::cout << "*s.end() = " << *s.end() << '\n';
    // s.rend() 指向第一个元素的前一个位置的逆向迭代器
    std::cout << "*s.rend() = " << *s.rend() << '\n';

    std::cout << "s.size() = " << s.size() << '\n';       // 返回集合长度

    s.erase(s.find(0)); // 删除集合中的 0
    s.erase(1);         // 删除集合中的 1

    s.insert(8);        // 8 已经存在集合中，会被去重

    for (auto& val : s) {
        std::cout << val << " ";
    }
    std::cout << '\n';

    std::cout << "s.count(4) = " << s.count(4) << '\n';     // 统计 4 在集合中出现的次数

    if (s.find(4) != s.end()) {                             // 查找 4 是否在集合
        std::cout << "in the set";
    }
    else {
        std::cout << "not in set";
    }
}


// 修改 set 默认排序
void UseSetSort() {

    // 仿函数
    std::set<int, std::greater<int>> s1 { 1, 2, 3, 4, 5, 6, 7 }; // set 默认是升序
    print(s1);

    // lambda
    auto cmp = [&](const auto& a, const auto& b) {
        return a > b;
    };
    std::set<int, decltype(cmp)> s2(cmp);
    s2 = { 8, 2, 3, 4, 5, 6, 7 };
    print(s2);

    // 使用 struct
    struct CmpS {
        // 需指定数据类型
        bool operator()(const int& a, const int& b) const {
            return a > b;
        }
    };
    std::set<int, CmpS> s3 { 8, 2, 3, 4, 5, 6, 7 };
    print(s3);

    // 函数对象
    class CmpC {
    public:
        // 需指明数据类型
        bool operator()(const int& a, const int& b) const {
            return a > b;
        }
    };
    std::set<int, CmpC> s4 { 8, 2, 3, 4, 5, 6, 7 };
    print(s4);

};


// set 用于查找坐标
void Coordinate() {
    std::set<int> s;
    auto points = std::vector<std::vector<int>> { { 1, 2 }, { 3, 4 } };
    for (const auto& point : points) {
        s.emplace(point[0] * 60001 + point[1]);
    }
    auto test_points = std::vector<std::vector<int>> { { 2, 5 }, { 1, 2 }, { 0, 2 } };
    // 判断 test_points 中是否有 points
    for (const auto& test_point : test_points) {
        std::cout << s.count(test_point[0] * 60001 + test_point[1]); // 010
    }
}

// set 可以使用 pair 作为键，unordered_set 使用 pair 必须 自己提供哈希算子
void SetKeyOfPair() {
    std::set<std::pair<int, int>> s;

}

void SetInsert() {
    std::set<int> s;
    s.insert(7);
    s.insert(9);
    s.insert(8);
    s.insert(6);
    if (s.find(7) != s.end()) {
        std::cout << *s.find(7) << '\n';
    }
}

void SetCount() {
    std::set<int> s;
    s.insert(2);
    s.insert(2);
    s.insert(2);
    s.insert(3);
    s.insert(4);

    std::cout << s.count(2) << '\n';
}

void SetLow() {
    std::set<int> s { 2, 4, 6, 8, 0 };
    print(s);
    std::cout << *s.lower_bound(7) << '\n';
}

int main() {
    // UsedSet();
    // // UseSetSort();
    // // Coordinate();
    // SetInsert();
    SetLow();
    return 0;
}