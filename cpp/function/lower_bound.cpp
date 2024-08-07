#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };
    std::vector<int> v(myints, myints + 8); // 10 20 30 30 20 10 10 20
    std::sort(v.begin(), v.end());          // 10 10 10 20 20 20 30 30

    auto low  = std::lower_bound(v.begin(), v.end(), 20); //  >=
    auto low2 = std::lower_bound(v.begin(), v.end(), 40); //
    auto up   = std::upper_bound(v.begin(), v.end(), 20); //  >
    auto up2  = std::upper_bound(v.begin(), v.end(), 40); //

    std::cout << "lower_bound at position "  << (low- v.begin())   << '\n';
    std::cout << "lower_bodun not in scope " << (low2 - v.begin()) << '\n';
    std::cout << "upper_bound at position "  << (up - v.begin())   << '\n';
    std::cout << "upper_bodun not in scope " << (up2 - v.begin())  << '\n';
    return 0;
}