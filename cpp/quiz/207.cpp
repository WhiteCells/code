#include <iostream>
#include <map>

using namespace std;

int main() {
    map<int, int> m;
    cout << m[42] << '\n'; // 0, 如果键不存在，[]运算符将插入一个元素。对于一个简单的 int，它插入 0。
    if (m.find(42) != m.end()) {
        cout << "have key of 42" << '\n';
    }
}