#include "../../head_file.h"

/*
problme: 630. 课程表 III
这里有 n 门不同的在线课程，按从 1 到 n 编号。给你一个数组 courses ，其中 courses[i] = [durationi, lastDayi] 表示第 i 门课将会 持续 上 durationi 天课，并且必须在不晚于 lastDayi 的时候完成。

你的学期从第 1 天开始。且不能同时修读两门及两门以上的课程。

返回你最多可以修读的课程数目。

示例 1：

输入：courses = [[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]
输出：3
解释：
这里一共有 4 门课程，但是你最多可以修 3 门：
首先，修第 1 门课，耗费 100 天，在第 100 天完成，在第 101 天开始下门课。
第二，修第 3 门课，耗费 1000 天，在第 1100 天完成，在第 1101 天开始下门课程。
第三，修第 2 门课，耗时 200 天，在第 1300 天完成。
第 4 门课现在不能修，因为将会在第 3300 天完成它，这已经超出了关闭日期。

示例 2：

输入：courses = [[1,2]]
输出：1

示例 3：

输入：courses = [[3,2],[4,3]]
输出：0

提示:
    1 <= courses.length <= 104
    1 <= durationi, lastDayi <= 104
url: https://leetcode.cn/problems/course-schedule-iii/description/
*/

class Solution {
public:
    int scheduleCourse(vector<vector<int>> &courses) {
        sort(courses.begin(), courses.end(), [&](vector<int> &v1, vector<int> &v2) {return v1[1] < v2[1];}); // 按照结束时间升序
        priority_queue<int> q; // 大顶堆
        int total = 0; // 修课耗时
        for (const auto &v : courses) {
            int t = v[0], d = v[1]; // 需要时间，结束时间
            if (total + t <= d) { // 能在 d 时间内修完当前课
                total += t; // 更新耗时
                q.emplace(t);
            }
            else if (!q.empty() && q.top() > t) { // 不能在 d 时间内修完当前可，但堆顶课比当前课所需要的时间长
                total -= q.top() - t; // 更新耗时
                q.pop(); // 弹出堆顶
                q.emplace(t);
            }
        }
        return q.size();
    }
};

int main() {
    vector<vector<int>> courese {
        { 100, 200 },
        { 200, 1300 },
        { 1000, 1250 },
        { 2000, 3200 }
    };
    // vector<vector<int>> courese {
    //     { 1, 2 },
    // };
    // vector<vector<int>> courese {
    //     { 3, 2 },
    //     { 4, 3 }
    // };
    cout << Solution().scheduleCourse(courese);

    return 0;
}