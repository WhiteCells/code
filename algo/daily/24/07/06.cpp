#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    long long countAlternatingSubarrays(vector<int>& nums) {
        long long res = 0, cur = 0;
        int pre = -1;
        for (int a : nums) {
            cur = (pre != a) ? cur + 1 : 1;
            pre = a;
            res += cur;
        }
        return res;
    }
};

int main() {
    
    return 0;
}