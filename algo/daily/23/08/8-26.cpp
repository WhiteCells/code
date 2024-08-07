#include "../../head_file.h"

/*
problme: 228. 汇总区间
给定一个  无重复元素 的 有序 整数数组 nums 。
返回 恰好覆盖数组中所有数字 的 最小有序 区间范围列表 。也就是说，nums 的每个元素都恰好被某个区间范围所覆盖，并且不存在属于某个范围但不属于 nums 的数字 x 。
列表中的每个区间范围 [a,b] 应该按如下格式输出：
    "a->b" ，如果 a != b
    "a" ，如果 a == b
输入：nums = [0,1,2,4,5,7]
输出：["0->2","4->5","7"]
解释：区间范围是：
[0,2] --> "0->2"
[4,5] --> "4->5"
[7,7] --> "7"
提示：
    0 <= nums.length <= 20
    -231 <= nums[i] <= 231 - 1
    nums 中的所有值都 互不相同
    nums 按升序排列
url: https://leetcode.cn/problems/summary-ranges/
*/

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        /* 防止下面 nums[0] 越界 */
        if (nums.empty()) {
            return {};
        }
        int start = nums[0], end = nums[0], pre = nums[0];
        vector<string> res;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] == pre + 1) {
                end = nums[i];
            }
            else if (nums[i] != pre + 1) {
                if (start == end) {
                    res.push_back(to_string(start));
                }
                else {
                    res.push_back(to_string(start) + "->" + to_string(end));
                }
                start = nums[i];
                end = nums[i];
            }
            pre = nums[i];
        }
        /* 后面的数据如果都是每个比前面一个多 1，则 end 一定 大于等于 start */
        if (end >= start) {
            if (end != start) {
                res.push_back(to_string(start) + "->" + to_string(end));
            }
            else {
                res.push_back(to_string(start));
            }
        }
        return res;
    }
};

class Solution2 {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        if (nums.empty()) {
            return {};
        }
        int start = 0, end = 0;
        vector<string> res;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i - 1] + 1) {
                ++end;
            }
            else {
                if (start == end) {
                    res.emplace_back(to_string(nums[start]));
                }
                else {
                    res.emplace_back(to_string(nums[start]) + "->" + to_string(nums[end]));
                }
                start = end = i;
            }
        }
        if (start == end) {
            res.emplace_back(to_string(nums[start]));
        }
        else {
            res.emplace_back(to_string(nums[start]) + "->" + to_string(nums[end]));
        }
        return res;
    }
};

class Solution3 {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;
        int i = 0;
        int n = nums.size();
        while (i < n) {
            int left = i;
            ++i;
            while (i < n && nums[i] == nums[i - 1] + 1) {
                ++i;
            }
            int right = i - 1;
            string str = to_string(nums[left]);
            if (left < right) {
                str += "->" + to_string(nums[right]);
            }
            res.push_back(str);
        }
        return res;
    }
};


int main() {
    vector<int> nums { 0, 1, 2, 4, 5, 7 };
    // vector<int> nums { -1 };
    // Solution s;
    // Solution2 s;
    Solution3 s;
    vector<string> res = s.summaryRanges(nums);
    for (const auto& str : res) {
        cout << str << '\n';
    }
    return 0;
}