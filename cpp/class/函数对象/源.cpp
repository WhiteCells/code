#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class MyCompare {
public:
    bool operator()(int value1, int value2) {
        return (value1 > value2);
    }
};

void test() {
    vector<int>v;

    v.push_back(20);
    v.push_back(50);
    v.push_back(30);
    v.push_back(40);
    v.push_back(10);

    // �������
    ::sort(v.begin(), v.end());
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        cout << *it << " "; // 10 20 30 40 50
    }
    cout << endl;

    // �޸�������򣬴����Ԫν�ʣ�������������
    ::sort(v.begin(), v.end(), MyCompare());
    for (vector<int>::iterator it2 = v.begin(); it2 != v.end(); ++it2) {
        cout << *it2 << " "; // 50 40 30 20 10
    }
    cout << endl;
}

int main() {
    test();
    system("pause");
    return 0;
}