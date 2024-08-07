#include "D:\distake\Coding\head_file.h"

class Solution {
public:
    string reverseLeftWords(string s, int n) {
        int slow = 0, fast = s.size();
        int len = s.size();
        s.resize(len + n);
        int count = n;
        while (count--) {
            s[fast++] = s[slow++];
        }
        slow = 0;
        fast = n;
        for (; fast < len; ++fast) {
            s[slow++] = s[fast];
        }
        s.resize(len);
        return s;
    }
    // 反转字符串，start、end 为物理下标
    void reverseStr(string& s, int start, int end) {
        for (int i = start, j = end; i < j; ++i, --j) {
            s[i] ^= s[j];
            s[j] ^= s[i];
            s[i] ^= s[j];
        }
    }
    string reverseLeftWords2(string s, int n) {
        // 反转 n 前面的字符串，n 为逻辑下标
        reverseStr(s, 0, n - 1);
        // 反转 n 后面的字符串
        reverseStr(s, n, s.size() - 1);
        // 反转 s 整个字符串
        reverseStr(s, 0, s.size() - 1);
        // 返回字符串
        return s;
    }
};

int main() {
    Solution s;
    string str = "lohel";
    cout << s.reverseLeftWords2(str, 2);
    return 0;
}