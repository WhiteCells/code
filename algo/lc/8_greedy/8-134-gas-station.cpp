#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-05-21 16:26:36
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-05-21 16:26:36
 * @Description: 134.加油站
 * https://leetcode.cn/problems/gas-station/
*/

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int sum = 0;         // 从前向后走统计剩余的汽油
        int min = INT32_MAX; // 每一次所剩下的汽油的最小值
        for (int i = 0; i < gas.size(); ++i) {
            sum += gas[i] - cost[i];
            if (sum < min) {
                min = sum;
            }
        }
        if (sum < 0) { // 总的剩余汽油 < 0，就不可能走完
            return -1;
        }
        if (min >= 0) { // 剩余汽油最小值 >= 0，说明每一段路的 gas >= cost，直接从第一个位置走就行
            return 0;
        }
        for (int i = gas.size() - 1; i >= 0; --i) { // 找到能将 min 变为非负的下标
            min += gas[i] - cost[i];
            if (min >= 0) {
                return i;
            }
        }
        return -1;
    }
};

class Solution2 {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int sum = 0;    // 总累加的汽油剩余量
        int curSum = 0; // 找到累加剩余汽油量持续 > 0 的一段
        int start = 0;  // 可能的起点
        for (int i = 0; i < gas.size(); ++i) {
            sum += gas[i] - cost[i];    // 累加总的汽油剩余量，用来判断能不能走完
            curSum += gas[i] - cost[i]; // 累加剩余汽油量需要一直保持 > 0 的 curSum
            if (curSum < 0) {           // 当前位置不能作为起点
                curSum = 0;             // 重新计算 curSum
                start = i + 1;          // 当前位置的下一个位置作为可能的起点，如果 i + 1 位置出现 curSum < 0，就继续变成当前的 i + 1
            }
        }
        if (sum < 0) {
            return -1;
        }
        return start;
    }
};

int main() {
    // vector<int> gas {1, 2, 3, 4, 5};
    // vector<int> cost {3, 4, 5, 1, 2};

    // vector<int> gas {2, 3, 4};
    // vector<int> cost {3, 4, 3};

    // vector<int> gas {3, 3, 4};
    // vector<int> cost {3, 4, 4};

    vector<int> gas {5, 1, 2, 3, 4};
    vector<int> cost {4, 4, 1, 5, 1};

    Solution s;
    cout << s.canCompleteCircuit(gas, cost);
    return 0;
}