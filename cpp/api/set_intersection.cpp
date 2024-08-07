#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

void test01() {
    vector<int> v1 { 3, 4, 5, 6 };
    vector<int> v2 { 4, 5, 6 };
    vector<int> v_target(min(v1.size(), v2.size())); 
    vector<int>::iterator end_it = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v_target.begin());
    for (const auto &ele : v_target) {
        cout << ele << " ";
    }
    cout << '\n';
}

int main() {
    test01();
    return 0;
}