#include "../../head_file.h"

/*
problme:

url:
*/

class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>> &prerequisites, vector<vector<int>> &queries) {
        vector<int> gree(numCourses, 0);
        vector<vector<int>> edge(numCourses);
        vector<vector<bool>> ispre(numCourses, vector<bool>(numCourses, false));
        for (const auto &p : prerequisites) {
            edge[p[0]].emplace_back(p[1]); // 建立连接
            ++gree[p[1]]; // 入度
        }
        /* 广度优先搜索 */
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (!gree[i]) {
                q.emplace(i);
            }
        }
        while (!q.empty()) {
            int g = q.front();
            q.pop();
            for (const auto &e : edge[g]) {
                ispre[g][e] = true; // g -> e
                for (int i = 0; i < numCourses; ++i) {
                    ispre[i][e] = ispre[i][e] | ispre[i][g];
                }
                --gree[e];
                if (!gree[e]) {
                    q.emplace(e);
                }
            }
        }
        vector<bool> res;
        for (const auto &q : queries) {
            res.emplace_back(ispre[q[0]][q[1]]);
        }
        return res;
    }
};

int main() {
    // [[0,1],[1,2],[2,3],[3,4]]
    // [[0,4],[4,0],[1,3],[3,0]]
    // [true,false,true,false]
    int numCourses = 5;
    vector<vector<int>> prerequisites {
        { 0, 1 },
        { 1, 2 },
        { 2, 3 },
        { 3, 4 }
    };
    vector<vector<int>> queries {
        { 0, 4 },
        { 4, 0 },
        { 1, 3 },
        { 3, 0 }
    };
    auto res = Solution().checkIfPrerequisite(numCourses, prerequisites, queries);
    for (const auto &ele : res) {
        cout << ele << '\n';
    }
    return 0;
}