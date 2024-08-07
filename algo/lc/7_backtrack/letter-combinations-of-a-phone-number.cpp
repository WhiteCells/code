#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// digits 2 ~ 9

class Solution {
private:
    string s;
    vector<string> result;
    const string keyMap[8] = { "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" }; // 每一个数对应的字符串
    void backtrack(int index, string digits) {
        if (index == digits.size()) {
            result.push_back(s);
            return;
        }
        int digit = digits[index] - '2';
        string key = keyMap[digit];
        for (int i = 0; i < key.size(); ++i) {
            s.push_back(key[i]);
            backtrack(index + 1, digits);
            s.pop_back();
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        if (digits.size() == 0) {
            return {};
        }
        backtrack(0, digits);
        return result;
    }
};

int main() {
    Solution s;
    vector<string> res = s.letterCombinations("23");
    for (const auto& s : res) {
        cout << s << '\n';
    }
    return 0;
}