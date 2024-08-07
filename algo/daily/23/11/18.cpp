#include "../../head_file.h"

/*
problme: 

url: 
 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    int maximumSum(vector<int>& nums) {
        int res = -1;
        unordered_map<int, int> mp; // bitSum : num
        for (const auto &num : nums) {
            int bs = bitSum(num);
            if (mp.count(bs)) {
                res = max(res, num + mp[bs]);
                mp[bs] = max(mp[bs], num);
            } else {
                mp[bs] = num;
            }
        }
        return res;
    }
private:
    int bitSum(int num) {
        int sum = 0;
        while (num) {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }
};

int main() {
    
    return 0;
}