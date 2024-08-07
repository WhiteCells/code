#include "D:\distake\Coding\head_file.h"

class Solution {
public:
    // void deleteSpace(string& s) {
    //     int fast = 0;
    //     int slow = 0;
    //     // 跳过开头空格
    //     while (fast < s.size() && s[fast] == ' ') {
    //         ++fast;
    //     } // fast 现在的位置不是空格
    //     // 处理中间的空格
    //     for (; fast < s.size(); ++fast) {
    //         if (fast - 1 > 0 && s[fast - 1] == s[fast] && s[fast] == ' ') continue;
    //         else s[slow++] = s[fast];
    //     }
    //     // 结尾空格直接重新调整字符串大小以达到删除目的
    //     if (slow - 1 > 0 && s[slow - 1] == ' ') {
    //         s.resize(slow - 1);
    //     }
    //     else {
    //         s.resize(slow);
    //     }
    // }
    // 删除多余的空格
    void removeExtraSpace(string& s) {
        int slow = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] != ' ') {
                if (slow != 0) s[slow++] = ' ';
                while (i < s.size() && s[i] != ' ') {
                    s[slow++] = s[i++];
                }
            }
        }
        s.resize(slow);
    }
    // 反转链表
    void reverseStr(string& s, int start, int end) {
        for (int i = start, j = end; i < j; ++i, --j) {
            s[i] ^= s[j];
            s[j] ^= s[i];
            s[i] ^= s[j];
        }
    }
    string reverseWords(string s) {
        removeExtraSpace(s);
        reverseStr(s, 0, s.size() - 1);
        int start = 0;
        for (int i = 0; i <= s.size(); ++i) {
            if (i == s.size() || s[i] == ' ') {
                reverseStr(s, start, i - 1);
                start = i + 1;
            }
        }
        return s;
    }
};

int main() {
    Solution s;
    string str = "   hello  world abc  ";
    cout << s.reverseWords(str); // "world hello"
    return 0;
}