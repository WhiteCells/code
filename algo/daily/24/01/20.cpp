#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/split-strings-by-separator/
 */

class Solution {
public:
    vector<string> splitWordsBySeparator(vector<string>& words, char separator) {
        vector<string> res;
        for (const auto &str : words) {
            string word;
            for (const auto &c : str) {
                if (separator == c) {
                    if (!word.empty()) {
                        res.emplace_back(word);
                        word.clear();
                    }
                } else {
                    word += c;
                }
            }
            if (!word.empty()) {
                res.emplace_back(word);
            }
        }
        return res;
    }
};

int main() {
    
    return 0;
}