#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/watering-plants/description/
 */

class Solution {
public:
    int wateringPlants(vector<int>& plants, int capacity) {
        int res = 0, n = plants.size(), cur = capacity;
        for (int i = 0; i < n; ++i) {
            if (cur < plants[i]) {
                res += i * 2 + 1;
                cur = capacity - plants[i];
            } else {
                ++res;
                cur -= plants[i];
            }
        }
        return res;
    }
};

int main() {
    vector<int> plants {2,2,3,3};
    int capacity = 5;
    cout << Solution().wateringPlants(plants, capacity) << endl;
    return 0;
}