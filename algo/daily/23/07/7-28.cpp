#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

class Solution {
public:
    // n = 3, relations = [[1,3],[2,3]], time = [3,2,5]
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        // vector<int> next[n];
        vector<vector<int>> next(n);
        vector<int> ind(n); // 入度
        for (auto& x : relations) {
            next[x[0] - 1].push_back(x[1] - 1);
            ++ind[x[1] - 1];
        }
        queue<int> q;
        vector<int> reach(n);
        for (int i = 0; i < n; ++i) {
            if (!ind[i]) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            auto x = q.front();
            q.pop();
            for (auto& j : next[x]) {
                reach[j] = max(reach[j], reach[x] + time[x]);
                if (--ind[j] == 0) {
                    q.push(j);
                }
            }
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res = max(res, reach[i] + time[i]);
        }
        return res;
    }
};

class Solution2 {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        vector<vector<int>> next(n); // 邻接表
        int din[n]; // 入度 
        memset(din, 0, sizeof(int));
        for (auto& r : relations) {
            next[r[0] - 1].push_back(r[1] - 1); // (x, y), next[x] = y;
            ++din[r[1] - 1]; // y 入度更新
        }
        queue<int> q;
        vector<int> tp(n); // topological sort
        for (int i = 0; i < n; ++i) {
            if (!din[i]) { // 入度 0 入队
                q.push(i);
            }
        }
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (auto& y : next[x]) {
                tp[y] = max(tp[y], tp[x] + time[x]);
                if (--din[y] == 0) {
                    q.push(y);
                }
            }
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res = max(res, tp[i] + time[i]);
        }
        return res;
    }
};

class Solution3 {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        vector<vector<int>> next(n); // 邻接表
        int din[n]; // 入度
        // vector<int> din(n);
        memset(din, 0, sizeof(din));
        // for (int i = 0; i < n; ++i) {
        //     din[i] = 0;
        // }
        for (auto& r : relations) {
            next[r[0] - 1].push_back(r[1] - 1); // (x, y), next[x] = y;
            ++din[r[1] - 1]; // y 入度更新
        }
        queue<int> q;
        vector<int> tp(n); // topological sort
        for (int i = 0; i < n; ++i) {
            if (!din[i]) { // 入度 0 入队
                q.push(i);
            }
        }
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (auto& y : next[x]) {
                tp[y] = max(tp[y], tp[x] + time[x]);
                if (--din[y] == 0) {
                    q.push(y);
                }
            }
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res = max(res, tp[i] + time[i]);
        }
        return res;
    }
};

int main() {
    Solution s;
    int n = 3;
    vector<vector<int>> relations{ { 1, 3 }, { 2, 3 } };
    vector<int> time{ 3, 2, 5 };
    cout << s.minimumTime(n, relations, time);
    return 0;
}