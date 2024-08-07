#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    vector<int> findOriginalArray(vector<int>& changed) {
        int n = changed.size();
        if (n & 1) {
            return {};
        }
        unordered_map<int, int> mp;
        for (const int &num : changed) {
            mp[num] += 1;
        }
        vector<int> res;
        bool is_first_zero = true;
        for (const int &num : changed) {
            if (num == 0 && is_first_zero) {
                is_first_zero = false;
            } else if (num == 0 && !is_first_zero) {
                is_first_zero = true;
                res.push_back(num);
            } else {
                if (mp[num * 2] > 0) {
                    mp[num] -= 1;
                    mp[num * 2] -= 1;
                    res.push_back(num);
                } else if (!(num & 1) && mp[num / 2] > 0) {
                    mp[num] -= 1;
                    mp[num / 2] -= 1;
                    res.push_back(num / 2);
                }
            }
        }
        if (!is_first_zero) {
            return {};
        }
        if (res.size() == n / 2) {
            return res;
        }
        return {};
    }
};

int main() {
    vector<int> nums {1,4,2,1};
    auto res = Solution().findOriginalArray(nums);
    for (const int n : res) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    return 0;
}