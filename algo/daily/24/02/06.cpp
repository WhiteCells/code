#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/p0NxJO/description
 */

class Solution {
public:
    int magicTower(vector<int>& nums) {
        priority_queue<int, vector<int>, greater<int>> q;
        int res = 0;
        long long hp = 1;
        int delay = 0;
        for (int num : nums) {
            if (num < 0) {
                q.push(num);
            }
            hp += num;
            if (hp <= 0) {
                ++res;
                delay += q.top();
                hp -= q.top();
                q.pop();
            }
        }
        hp += delay;
        return hp <= 0 ? -1 : res;
    }
};

int main() {
    vector<int> nums {100, 100, 100, -250, -60, -140, -50, -50, 100, 150};
    cout << Solution().magicTower(nums) << endl;
    return 0;
}