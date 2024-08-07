#include "../../head_file.h"

/*
problme: 7004. 判别首字母缩略词
给你一个字符串数组 words 和一个字符串 s ，请你判断 s 是不是 words 的 首字母缩略词 。
如果可以按顺序串联 words 中每个字符串的第一个字符形成字符串 s ，则认为 s 是 words 的首字母缩略词。例如，"ab" 可以由 ["apple", "banana"] 形成，但是无法从 ["bear", "aardvark"] 形成。
如果 s 是 words 的首字母缩略词，返回 true ；否则，返回 false 。
输入：words = ["alice","bob","charlie"], s = "abc"
输出：true
解释：words 中 "alice"、"bob" 和 "charlie" 的第一个字符分别是 'a'、'b' 和 'c'。因此，s = "abc" 是首字母缩略词。
提示：
    1 <= words.length <= 100
    1 <= words[i].length <= 10
    1 <= s.length <= 100
    words[i] 和 s 由小写英文字母组成
url: https://leetcode.cn/problems/check-if-a-string-is-an-acronym-of-words/
@Author: Eorys
@Date: 2023-08-20 07:01:50
@Last Modified by: Eorys
@Last Modified time: 2023-08-20 07:01:50
@Description:
*/

class Solution {
public:
    bool isAcronym(vector<string>& words, string s) {
        if (s.size() > words.size()) {
            return false;
        }
        for (int i = 0; i < words.size(); ++i) {
            if (words[i][0] != s[i]) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    vector<string> words { "abcd", "cde", "edf" };
    string str = "ace";
    Solution s;
    cout << s.isAcronym(words, str) << '\n';
    return 0;
}