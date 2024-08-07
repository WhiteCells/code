#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/count-the-repetitions/
 */

// TODO
class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        unordered_map<int, pair<int, int>> mp;
        int ans = 0;
        int len1 = s1.size(), len2 = s2.size();
        int index1 = 0, index2 = 0;
        while (index1 / len1 < n1) {
            if (index1 % len1 == len1 - 1) {
                // 出现循环
                if (mp.count(index2 % len2)) {
                    auto [i1, i2] = mp[index2 % len2];
                    int cnt_s1 = (index1 - i1) / len1; // s1 当前 i 减去上一次出现的 i，结果除以 s1 长度
                    int cnt_s2 = (index2 - i2) / len2; // s2 当前 i 减去上一次出现的 i，结果除以 s2 长度
                    int cnt_cycle = (n1 - 1 - index1 / len1) / cnt_s1; // 循环次数 
                    ans += cnt_cycle * cnt_s2;
                    index1 += cnt_cycle * (index1 - i1); 
                } else {
                    mp[index2 % len2] = {index1, index2};
                }
            }
            if (s1[index1 % len1] == s2[index2 % len2]) {
                if (index2 % len2 == len2 - 1) {
                    ++ans;
                }
                ++index2;
            }
            ++index1;
        }
        return ans / n2;
    }
};

int main() {
    
    return 0;
}