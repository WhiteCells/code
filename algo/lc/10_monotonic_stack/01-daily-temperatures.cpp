#include "../../head_file.h"

// https://leetcode.cn/problems/daily-temperatures/

// 输入: temperatures = [73,74,75,71,69,72,76,73]
// 输出: [1,1,4,2,1,1,0,0]

// 暴力，超时
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> res(n, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (temperatures[j] > temperatures[i]) {
                    res[i] = j - i;
                    break;
                }
            }
        }
        return res;
    }
};

// 单调栈
class Solution2 {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        stack<int> s;
        vector<int> res(n, 0);
        for (int i = 0; i < n; ++i) {
            while (!s.empty() && temperatures[i] > temperatures[s.top()]) {
                res[s.top()] = i - s.top();
                s.pop();
            }
            s.push(i);
        }
        return res;
    }
};


int main() {
    Solution s;
    // auto temperatures = vector<int> { 73, 74, 75, 71, 69, 72, 76, 73 };
    auto temperatures = vector<int> { 30, 40, 50, 60 };
    auto res = s.dailyTemperatures(temperatures);
    for (auto& val : res) {
        cout << val << ' ';
    }
    return 0;
}