#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

void test() {
    vector<bool> v1 {true, false, true, false, true, true};
    vector<bool> v2;
    v2.resize(v1.size());
    // logical_not
    transform(v1.begin(), v1.end(), v2.begin(), logical_not<bool>()); // 搬运
}

int main() {
    test();
    return 0;
}