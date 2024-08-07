#include "../../head_file.h"

/*
problme: 

url: 
 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        vector<int> pairs;
        sort(potions.begin(), potions.end());
        for (const auto &spell : spells) {
            long long target = (spell + success - 1) / spell - 1;
            pairs.emplace_back(potions.end() - (upper_bound(potions.begin(), potions.end(), target)));
        }
        return pairs;
    }
};

int main() {
    vector<int> spells { 5, 1, 3 }, potions { 1, 2, 3, 4, 5 };
    long long success = 7;
    auto res = Solution().successfulPairs(spells, potions, success);
    for (const auto &ele : res) {
        cout << ele << ' ';
    }
    cout << endl;
    return 0;
}