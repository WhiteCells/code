#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void test() {
    vector<int> v1;
    for (int i = 0; i < 10; ++i) { v1.push_back(i); }
    class Print {
    public:
        void operator()(const int &val) { cout << val << ' '; }
    };
    for_each(v1.begin(), v1.end(), Print());
    cout << endl;
}

int main() {
    test();
    return 0;
}

