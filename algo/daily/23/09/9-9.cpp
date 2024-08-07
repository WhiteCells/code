#include "../../head_file.h"

/*
problme:
你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。

在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。

    例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。

请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。
输入：numCourses = 2, prerequisites = [[1,0]]
输出：true
解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。
提示：

    1 <= numCourses <= 2000
    0 <= prerequisites.length <= 5000
    prerequisites[i].length == 2
    0 <= ai, bi < numCourses
    prerequisites[i] 中的所有课程对 互不相同
url: https://leetcode.cn/problems/course-schedule/
*/

/*
    深搜
 */
class Solution {
private:
    vector<vector<int>> edges; // 拓扑排序边的关系
    vector<int> visited; // 深搜访问标记
    bool valid = true; // 值是否有效

public:
    void dfs(int u) {
        visited[u] = 1;
        for (int v : edges[u]) {
            if (visited[v] == 0) {
                dfs(v);
                if (!valid) {
                    return;
                }
            }
            else if (visited[v] == 1) {
                valid = false;
                return;
            }
        }
        visited[u] = 2;
    }

    bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
        /* 建立边关系 */
        edges.resize(numCourses);
        visited.resize(numCourses);
        // 
        for (const auto &info: prerequisites) {
            edges[info[1]].push_back(info[0]);
        }
        for (int i = 0; i < numCourses && valid; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        return valid;
    }
};

int main() {
    int numCourses = 20;
    vector<vector<int>> prerequisites {
        // a <- b
        { 0, 10 },
        { 3, 18 },
        { 5, 5, },
        { 6, 11 },
        { 11, 14 },
        { 13, 1 },
        { 15, 1 },
        { 17, 4 }
    }; // false
    cout << Solution().canFinish(numCourses, prerequisites) << '\n';
    return 0;
}