#include "D:\distake\Coding\head_file.h"

class Solution {
public:
    string removeDuplicates(string s) {
        stack<char> charStack;
        for (auto& c : s) {
            if (!charStack.empty() && charStack.top() == c) {
                charStack.pop();
            }
            else {
                charStack.push(c);
            }
        }
        int count1 = charStack.size();
        int count2 = charStack.size();
        while (count1--) {
            s[count1] = charStack.top();
            charStack.pop();
        }
        s.resize(count2);
        return s;
    }
};

class Solution2 {
public:
    string removeDuplicates(string s) {
        string res;
        for (auto& c : s) {
            if (res.empty() || res.back() != c) {
                res.push_back(c);
            }
            else {
                res.pop_back();
            }
        }
        return res;
    }
};

int main() {
    Solution2 s;
    string str = "aabccdde";
    cout << s.removeDuplicates(str);
    return 0;
}