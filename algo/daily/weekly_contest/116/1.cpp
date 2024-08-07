#include "../../head_file.h"

/*
problme:
输入：nums = [1,2,1]
输出：15
解释：六个子数组分别为：
[1]: 1 个互不相同的元素。
[2]: 1 个互不相同的元素。
[1]: 1 个互不相同的元素。
[1,2]: 2 个互不相同的元素。
[2,1]: 2 个互不相同的元素。
[1,2,1]: 2 个互不相同的元素。
所有不同计数的平方和为 12 + 12 + 12 + 22 + 22 + 22 = 15 。
url:
 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    int sumCounts(vector<int> &nums) {
        int res = 0;
        for (int i = 0; i < nums.size(); ++i) { // 开始下标
            for (int j = 0; j < nums.size() - i; ++j) { // 长度
                unordered_set<int> st;
                for (int k = 0; k <= j; ++k) { // 向后移动位
                    st.insert(nums[i + k]);
                }
                res += pow(st.size(), 2);
            }
        }
        return res;
    }
};

int main() {
    vector<int> nums { 1, 2, 1 };
    // vector<int> nums { 2, 2 };
    cout << Solution().sumCounts(nums) << endl;
    return 0;
}