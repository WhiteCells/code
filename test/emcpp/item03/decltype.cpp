#include <iostream>
#include <vector>
#include <deque>

// template<typename Container, typename Index> // C++11
// auto authAndAccess(Container &c, Index i) -> decltype(c[i]) {
//     // authenticateUser();
//     return c[i];
// }

// template<typename Container, typename Index> // C++14
// decltype(auto) authAndAccess(Container &c, Index i) {
//     return c[i];
// }

// template<typename Container, typename Index> // C++14
// decltype(auto) authAndAccess(Container &&c, Index i) {
//     return c[i];
// }

// template<typename Container, typename Index> // C++14
// decltype(auto) authAndAccess(Container &&c, Index i) {
//     // authenticateUser();
//     return std::forward<Container>(c)[i];
// }

template<typename Container, typename Index> // C++11
auto authAndAccess(Container &&c, Index i) -> decltype(std::forward<Container>(c)[i]) {
    // authenticateUser();
    return std::forward<Container>(c)[i];
}

class Weight {
public:
    Weight() = default;
    Weight(const Weight &) = default;
};

decltype(auto) f1() {
    int *x = new int(0);
    return (x);
}

// decltype(auto) f2() {
//     int x = 01;
//     return (x);
// }

int main() {
    std::vector<int> v { 1, 2, 3 };
    std::cout << authAndAccess(v, 1) << std::endl;
    authAndAccess(v, 1) = 100;
    std::cout << authAndAccess(v, 1) << std::endl;

    f1() = nullptr;
    // f2() = 2;

//     Weight w;
//     const Weight &cw = w;
// 
//     auto my_weight1 = cw; // auto 类型推导
//                           // my_weight1 类型为 Weight
// 
//     decltype(auto) my_weight2 = cw; // decltype 类型推导
//                                     // my_weight2 类型是 const Weight &
// 
//     std::cout << authAndAccess(std::vector<int>{ 1, 2, 3 }, 2) << std::endl;
    return 0;
}