#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0, n = height.size(); // 1 <= n <= 2 * 10^4
        // 找到最高点，及其下标
        int max_height = height[0], max_index = 0;
        for (int i = 1; i < n; ++i) {
            if (height[i] > max_height) {
                max_height = height[i];
                max_index = i;
            }
        }
        // 从左向右遍历到最高点
        int tmp = height[0];
        for (int i = 1; i < max_index; ++i) {
            if (tmp > height[i]) {
                ans += tmp - height[i];
            }
            else {
                tmp = height[i];
            }
        }
        // 从右向左遍历到最高点
        tmp = height[n - 1];
        for (int i = n - 2; i > max_index; --i) {
            if (tmp > height[i]) {
                ans += tmp - height[i];
            }
            else {
                tmp = height[i];
            }
        }
        return ans;
    }
};

class Solution2 {
public:
    int trap(vector<int>& height) {
        int ans = 0, n = height.size();

    }
};

int main() {
    Solution s;
    auto height = vector<int>{ 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
    cout << s.trap(height);
    return 0;
}