#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/boats-to-save-people/description/
 */

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int n = people.size(), res = 0;
        for (int i = 0, j = n - 1; i <= j; ) {
            if (i == j) {
                ++res;
                break;
            }
            if (people[j] >= limit) {
                --j;
            } else if (people[j] + people[i] > limit) {
                --j;
            } else {
                ++i;
                --j;
            }
            ++res;
        }
        return res;
    }
};

int main() {
    
    return 0;
}