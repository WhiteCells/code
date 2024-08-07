#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/count-unique-characters-of-all-substrings-of-a-given-string/
 */

class Solution {
public:
    int uniqueLetterString(string s) {
        // 用哈希表存放同个字母出现的位置，按照 某个字符以唯一的形式出现在子串 来划定区间
        unordered_map<char, vector<int>> mp;
        for (int i = 0; i < s.size(); ++i) {
            mp[s[i]].push_back(i);
        }
        int res = 0;
        for (const auto &[_, v] : mp) {
            // 双指针
            int head = -1, tail;
            for (int i = 0; i < v.size(); ++i) {
                // 判断当前字母出现的次数是否大于 1 (前提:略去当前字符已经循环过的区间)，
                // 若大于 1，则可以对当前字母划定区间，保证当前字母出现在子串中是唯一的
                if (i < v.size() - 1) {
                    tail = v[i + 1];
                } else {
                    // 当前字符为最后一个位置，尾指针指到主串最后一个字符的下一个位置(即字符串的长度)
                    tail = s.size();
                }
                res += (v[i] - head) * (tail - v[i]);
                // 需要划定多个区间的时候，头指针需要更新，下一个区间的头指针是当前的位置
                head = v[i];
            }
        }
        return res;
    }
};

int main() {
    string s = "ABA";
    cout << Solution().uniqueLetterString(s) << endl;
    return 0;
}