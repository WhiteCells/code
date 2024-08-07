#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        backtrack(1, n, k);
        return result;
    }
private:
    void backtrack(int start, int end, int k) {
        if (path.size() == k) {
            result.push_back(path);
            return;
        }
        for (int i = start; i <= end; ++i) {
            path.push_back(i);
            backtrack(i + 1, end, k);
            path.pop_back();
        }
    }
    vector<vector<int>> result;
    vector<int> path;
};

// 回溯剪枝
class Solution2 {
public:
    vector<vector<int>> combine(int n, int k) {
        backtrack(1, n, k);
        return result;
    }
private:
    void backtrack(int start, int end, int k) {
        if (path.size() == k) {
            result.push_back(path);
            return;
        }
        for (int i = start; i <= end - (k - path.size()) + 1; ++i) { // 剪枝操作
            path.push_back(i);
            backtrack(i + 1, end, k);
            path.pop_back();
        }
    }
    vector<vector<int>> result;
    vector<int> path;
};

int main() {
    Solution2 s;
    vector<vector<int>> rev = s.combine(4, 2);
    for (auto& v : rev) {
        for (auto& val : v) {
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}