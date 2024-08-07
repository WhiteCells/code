#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/maximum-swap/description/
 */

class Solution {
public:
    int maximumSwap(int num) {
        string str = to_string(num);
        int res = num;
        for (int i = 0; i < str.size(); i++) {
            for (int j = i + 1; j < str.size(); j++) {
                swap(str[i], str[j]);
                res = max(res, stoi(str));
                swap(str[i], str[j]);
            }
        }
        return res;
    }
};

int main() {
    int num = 98368;
    cout << Solution().maximumSwap(num) << endl;
    return 0;
}