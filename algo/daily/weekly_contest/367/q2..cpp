#include "../../head_file.h"

/*
problme: 100084. 最短且字典序最小的美丽子字符串

给你一个二进制字符串 s 和一个正整数 k 。

如果 s 的某个子字符串中 1 的个数恰好等于 k ，则称这个子字符串是一个 美丽子字符串 。

令 len 等于 最短 美丽子字符串的长度。

返回长度等于 len 且字典序 最小 的美丽子字符串。如果 s 中不含美丽子字符串，则返回一个 空 字符串。

对于相同长度的两个字符串 a 和 b ，如果在 a 和 b 出现不同的第一个位置上，a 中该位置上的字符严格大于 b 中的对应字符，则认为字符串 a 字典序 大于 字符串 b 。

    例如，"abcd" 的字典序大于 "abcc" ，因为两个字符串出现不同的第一个位置对应第四个字符，而 d 大于 c 。

示例 1：

输入：s = "100011001", k = 3
输出："11001"
解释：示例中共有 7 个美丽子字符串：
1. 子字符串 "100011001" 。
2. 子字符串 "100011001" 。
3. 子字符串 "100011001" 。
4. 子字符串 "100011001" 。
5. 子字符串 "100011001" 。
6. 子字符串 "100011001" 。
7. 子字符串 "100011001" 。
最短美丽子字符串的长度是 5 。
长度为 5 且字典序最小的美丽子字符串是子字符串 "11001" 。

示例 2：

输入：s = "1011", k = 2
输出："11"
解释：示例中共有 3 个美丽子字符串：
1. 子字符串 "1011" 。
2. 子字符串 "1011" 。
3. 子字符串 "1011" 。
最短美丽子字符串的长度是 2 。
长度为 2 且字典序最小的美丽子字符串是子字符串 "11" 。

示例 3：

输入：s = "000", k = 1
输出：""
解释：示例中不存在美丽子字符串。

提示：

    1 <= s.length <= 100
    1 <= k <= s.length


url: https://leetcode.cn/problems/shortest-and-lexicographically-smallest-beautiful-string/description/
 */

// time complexity: O(n^3)
// spatial complexity: O(1)
// 暴力必须枚举 k, 因为要求返回长度等于 len(最短 美丽子字符串的长度) 且字典序 最小 的美丽子字符串
// 要先考虑长度最短的前提下字典序最小
class Solution1 {
public:
    string shortestBeautifulSubstring(string s, int k) {
        // 枚举长度, 包含 k 个 1, 字符串长度至少 k
        for (int i = k; i < s.size() + 1; ++i) { // O(n)
            string res {};
            for (int j = 0; j < s.size(); ++j) { // O(n)
                string subs = s.substr(j, i);    // j(包含) 开始向后 i - 1 位
                int cnt = 0;
                if (("" == res || subs < res) && k == [&subs, &cnt] { // O(n)
                    for (const auto &c : subs) {
                        cnt += c - '0';
                    }
                    return cnt;
                }()) {
                    res = subs;
                }
            }
            if (!res.empty()) {
                return res;
            }
        }
        return "";
    }
};

// time complexity: O()
// spatial complexity: O()
// 滑动窗口
class Solution3 {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int left = 0, right = 0, cnt1 = 0;
        string res {};
        while (right < s.size()) {
            cnt1 += s[right] - '0';
            // 窗口内 1 的个数 > k 或者 第一个字符为 '0' 时移动左端点
            while (cnt1 > k || '0' == s[left]) {
                cnt1 -= s[left] - '0';
                ++left;
            }
            if (cnt1 == k) {
                string subs(s.begin() + left, s.begin() + right + 1);
                // 1. res 为空
                // 2. res 的长度小于 subs 长度
                // 3. res 的长度等于 subs 长度 且 res 字典序 比 subs 大
                if (res.empty() || res.size() > subs.size() || (res.size() == subs.size() && res > subs)) {
                    res = subs;
                }
            }
            ++right;
        }
        return res;
    }
};

int main() {
    // string s = "100011001";
    // int k = 3;
    // string s = "11000111";
    // int k = 1;
    // string s = "111111110010001010";
    // int k = 11;
    string s = "001110101101101111"; // "10101101101111"
    int k = 10;
    // string s = "1111111011111"; // "1111111011111"
    // int k = 12;
    // cout << Solution1().shortestBeautifulSubstring(s, k) << '\n';
    cout << Solution3().shortestBeautifulSubstring(s, k) << '\n';
    return 0;
}