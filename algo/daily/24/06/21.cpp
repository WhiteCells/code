#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/6CE719/description/
 */

class Solution {
public:
    int temperatureTrend(vector<int>& temperatureA, vector<int>& temperatureB) {
        int n = temperatureA.size();
        int res = 0, cur = 0;
        for (int i = 0; i + 1 < n; ++i) {
            int diff1 = temperatureA[i + 1] - temperatureA[i];
            int diff2 = temperatureB[i + 1] - temperatureB[i]; 
            bool is_same = (diff1 > 0 && diff2 > 0) || (diff1 < 0 && diff2 < 0) || (diff1 == 0 && diff2 == 0); 
            if (is_same) {
                ++cur;
                res = max(res, cur);
            } else {
                cur = 0;
            }
        }
        return res;
    }
};

int main() {
    
    return 0;
}