#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    vector<int> distributeCandies(int candies, int num_people) {
        vector<int> res(num_people);
        int cur = 1, i = 0;
        while (cur <= candies) {
            res[i] += cur;
            candies -= cur;
            ++cur;
            ++i;
            if (i >= num_people) {
                i = 0;
            }
        }
        res[i] += candies;
        return res;
    }
};

int main() {
    int candies = 10, num_people = 3;
    auto res = Solution().distributeCandies(candies, num_people);
    for (const auto &ele : res) {
        std::cout << ele << " ";
    }
    return 0;
}