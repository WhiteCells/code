#include "D:\distake\Coding\head_file.h"

class Solution {
public:
    // 一个数每一位的平方的和
    void sumEveryBitSquare(int& n) {
        int sum = 0;
        while (n) {
            sum += pow(n % 10, 2);
            n /= 10;
        }
        n = sum;
    }

    bool isHappy1(int n) {
        unordered_set<int> unset;
        while (1) {
            sumEveryBitSquare(n);
            if (n == 1) return true;
            // cout << n << endl; // 测试断点

            // 找到重复的 n，就说明不是开心数
            if (unset.find(n) != unset.end()) {
                return false;
            }
            // 暂时无法确定就继续向set中放 n
            unset.insert(n);
        }
    }
};

int main() {
    Solution s;
    cout << s.isHappy1(19);
    return 0;
}