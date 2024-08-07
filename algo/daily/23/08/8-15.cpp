#include "../../head_file.h"

/*
problme: 833. 字符串中的查找与替换
你会得到一个字符串 s (索引从 0 开始)，你必须对它执行 k 个替换操作。替换操作以三个长度均为 k 的并行数组给出：indices, sources, targets。
要完成第 i 个替换操作:
    检查 子字符串  sources[i] 是否出现在 原字符串 s 的索引 indices[i] 处。
    如果没有出现， 什么也不做 。
    如果出现，则用 targets[i] 替换 该子字符串。
例如，如果 s = "abcd" ， indices[i] = 0 , sources[i] = "ab"， targets[i] = "eee" ，那么替换的结果将是 "eeecd" 。
所有替换操作必须 同时 发生，这意味着替换操作不应该影响彼此的索引。测试用例保证元素间不会重叠 。
    例如，一个 s = "abc" ，  indices = [0,1] ， sources = ["ab"，"bc"] 的测试用例将不会生成，因为 "ab" 和 "bc" 替换重叠。
在对 s 执行所有替换操作后返回 结果字符串 。
子字符串 是字符串中连续的字符序列。

输入：s = "abcd", indexes = [0,2], sources = ["a","cd"], targets = ["eee","ffff"]
输出："eeebffff"
解释：
"a" 从 s 中的索引 0 开始，所以它被替换为 "eee"。
"cd" 从 s 中的索引 2 开始，所以它被替换为 "ffff"。
数据范围：
    1 <= s.length <= 1000
    k == indices.length == sources.length == targets.length
    1 <= k <= 100
    0 <= indexes[i] < s.length
    1 <= sources[i].length, targets[i].length <= 50
    s 仅由小写英文字母组成
    sources[i] 和 targets[i] 仅由小写英文字母组成
url: https://leetcode.cn/problems/find-and-replace-in-string/description/
@Author: Eorys
@Date: 2023-08-15 06:42:21
@Last Modified by: Eorys
@Last Modified time: 2023-08-15 06:42:21
@Description:
*/

class Solution {
public:
    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {
        unordered_map<int, int> mp; // val : index;
        for (int i = 0; i < indices.size(); ++i) {
            mp[indices[i]] = i;
        }
        string res;
        for (int i = 0; i < s.size(); ++i) {
            if (mp.find(i) != mp.end()) {
                int index = mp[i]; // sources target index
                string source = sources[index];
                string target = targets[index];
                bool match = true;
                for (int j = i, k = 0; j < i + source.size(); ++j, ++k) {
                    if (source[k] != s[j]) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    res += target;
                    i += source.size() - 1;
                }
                else {
                    res += s[i];
                }
            }
            else {
                res += s[i];
            }
        }
        return res;
    }
};


int main() {
    // string str = "abcd";
    // vector<int> indices { 0, 2 };
    // vector<string> sources { "a", "cd" };
    // vector<string> target { "eee", "ffff" };

    string str = "abcd";
    vector<int> indices { 0, 2 };
    vector<string> sources { "ab", "ec" };
    vector<string> target { "eee", "ffff" };

    Solution s;
    cout << s.findReplaceString(str, indices, sources, target) << '\n';

    return 0;
}