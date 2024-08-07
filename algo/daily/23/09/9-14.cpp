#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    vector<vector<int>> queensAttacktheKing(vector<vector<int>> &queens, vector<int> &king) {
        vector<vector<int>> res;
        for (const auto &q : queens) {
            /* 水平和垂直方向 */
            if (king[0] == q[0] || king[1] == q[1]) {
                res.push_back({ q[0], q[1] });
            }
            /* 对角线方向 */
            else if ((king[0] - q[0] == king[1] - q[1]) || (-1 == (king[1] - q[1]) / (king[0] - q[0]))) {
                res.push_back({ q[0], q[1] });
            }
        }
        return res;
    }
};

class Solution2 {
public:
    vector<vector<int>> queensAttacktheKing(vector<vector<int>> &queens, vector<int> &king) {
        vector<vector<int>> res;
        /*
            遍历 king 水平、垂直、对角线方向
            由于 king 最多被 8 个 queens 攻击
            只需要在 8 个方向上去各找第一个遇到的 queens（不一定存在）
         */
        unordered_map<int, int> mp;
        for (const auto &q : queens) {
            mp.emplace(make_pair(q[0] + q[1] * 100, q[0]));
        }
        /* 8 个方向 */
        vector<array<int, 2>> direction {
            { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 },
            { -1, 1 }, { 1, 1 }, { 1, -1 }, { -1, -1 }
        };
        /* 遍历 king 的 8 个方向 */
        for (const auto &dire : direction) {
            int x = king[0], y = king[1];
            while (x >= 0 && x < 8 && y >= 0 && y < 8) {
                x += dire[0];
                y += dire[1];
                if (mp.count(x + y * 100)) {
                    res.push_back({ x, y });
                    break; // 一个方向只需要找到第一个遇到的 queens
                }
            }
        }
        return res;
    }
};

class Solution3 {
public:
    vector<vector<int>> queensAttacktheKing(vector<vector<int>> &queens, vector<int> &king) {
        vector<vector<int>> res;
        /*
            遍历 king 水平、垂直、对角线方向
            由于 king 最多被 8 个 queens 攻击
            只需要在 8 个方向上去各找第一个遇到的 queens（不一定存在）
         */
        unordered_set<int> s;
        for (const auto &q : queens) {
            s.emplace(q[0] + q[1] * 100);
        }
        /* 8 个方向 */
        vector<array<int, 2>> direction {
            { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 },
            { -1, 1 }, { 1, 1 }, { 1, -1 }, { -1, -1 }
        };
        /* 遍历 king 的 8 个方向 */
        for (const auto &dire : direction) {
            int x = king[0], y = king[1];
            while (x >= 0 && x < 8 && y >= 0 && y < 8) {
                x += dire[0];
                y += dire[1];
                if (s.count(x + y * 100)) {
                    res.push_back({ x, y });
                    break; // 一个方向只需要找到第一个遇到的 queens
                }
            }
        }
        return res;
    }
};

// [[0,1],[1,0],[4,0],[0,4],[3,3],[2,4]], king = [0,0]
int main() {
    vector<vector<int>> queens {
        { 0, 1 },
        { 1, 0 },
        { 4, 0 },
        { 0, 4 },
        { 3, 3 },
        { 2, 4 },
    };
    vector<int> king { 0, 0 };
    auto res = Solution3().queensAttacktheKing(queens, king);
    for (const auto &v : res) {
        for (const auto &ele : v) {
            cout << ele << ' ';
        }
        cout << '\n';
    }
    return 0;
}