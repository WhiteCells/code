#include "../../head_file.h"

/*
problme:
给你一个整数数组 ranks ，表示一些机械工的 能力值 。ranksi 是第 i 位机械工的能力值。能力值为 r 的机械工可以在 r * n2 分钟内修好 n 辆车。

同时给你一个整数 cars ，表示总共需要修理的汽车数目。

请你返回修理所有汽车 最少 需要多少时间。

注意：所有机械工可以同时修理汽车。
输入：ranks = [4,2,3,1], cars = 10
输出：16
解释：
- 第一位机械工修 2 辆车，需要 4 * 2 * 2 = 16 分钟。
- 第二位机械工修 2 辆车，需要 2 * 2 * 2 = 8 分钟。
- 第三位机械工修 2 辆车，需要 3 * 2 * 2 = 12 分钟。
- 第四位机械工修 4 辆车，需要 1 * 4 * 4 = 16 分钟。
16 分钟是修理完所有车需要的最少时间。
提示：

    1 <= ranks.length <= 105
    1 <= ranks[i] <= 100
    1 <= cars <= 106

url:
*/

class Solution {
public:
    long long repairCars(vector<int> &ranks, int cars) {
        long long left = 1, right = INT64_MAX;
        /* mid 分钟是否能全部修完 */
        auto f = [&](long long mid) {
            long long cnt = 0;
            for (const auto &rank : ranks) {
                cnt += sqrt(mid / rank);
            }
            return cnt >= cars;
        };
        while (left < right) {
            long long mid = left + (right - left) / 2;
            // long long mid = left + right >> 1;
            // long long mid = left + (right - left) >> 1; // error
            if (f(mid)) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }
        return left;
    }
};

int main() {
    vector<int> ranks { 4, 2, 3, 1 };
    int cars = 10;

    cout << Solution().repairCars(ranks, cars) << '\n';
    return 0;
}