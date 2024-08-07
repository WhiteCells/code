#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/minimum-additions-to-make-valid-string/
 */

// TODO
class Solution {
public:
    int addMinimum(string word) {
        
    }
};

// 
class Solution2 {
public:
    int addMinimum(string word) {
        int res = 0;
        while (!word.empty()) {
            if (word.size() >= 3 && *(word.end() - 1) > *(word.end() - 2) && *(word.end() - 2) > *(word.end() - 3)) {
                word.pop_back();
                word.pop_back();
            } else if (word.size() >= 2 && *(word.end() - 1) > *(word.end() - 2)) {
                res += 1;
                word.pop_back();
            } else {
                res += 2;
            }
            word.pop_back();
        }
        return res;
    }
};


int main() {
    cout << Solution2().addMinimum("abccb") << endl;
    return 0;
}