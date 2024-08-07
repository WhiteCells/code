#include "../../head_file.h"

/*
problme: 

url:
 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    int minProcessingTime(vector<int> &processorTime, vector<int> &tasks) {
        sort(processorTime.begin(), processorTime.end()); // 升序
        sort(tasks.begin(), tasks.end(), greater<int>()); // 降序
        int m = tasks.size();
        int res = -1;
        // 每 4 个任务执行之后 切换 执行时间
        for (int i = 0; i < m; ++i) { // 遍历 tasks
            // 每 4 个一组
            res = max(processorTime[i / 4] + tasks[i], res);
        }
        return res;
    }
};

int main() {
    vector<int> processorTime { 8, 10 }, tasks { 2, 2, 3, 1, 8, 7, 4, 5 };
    cout << Solution().minProcessingTime(processorTime, tasks) << endl;
    return 0;
}