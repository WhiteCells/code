#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/watering-plants-ii/
 */

class Solution {
public:
    int minimumRefill(vector<int>& plants, int capacityA, int capacityB) {
        int res = 0, n = plants.size(), cura = capacityA, curb = capacityB;
        for (int i = 0, j = n - 1; i <= j; ++i, --j) {
            if (i == j) {
                if (max(cura, curb) < plants[i]) {
                    ++res;
                }
                break;
            }
            if (cura < plants[i]) {
                ++res;
                cura = capacityA;
            }
            if (curb < plants[j]) {
                ++res;
                curb = capacityB;
            }
            curb -= plants[j];
            cura -= plants[i];
        }
        return res;
    }
};


int main() {
    vector<int> plants {7,7,7,7,7,7,7};
    int capacityA = 8, capacityB = 7;
    cout << Solution().minimumRefill(plants, capacityA, capacityB) << endl;
    return 0;
}