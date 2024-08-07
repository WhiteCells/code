#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>

using namespace std;
//https://leetcode.cn/problems/walking-robot-simulation/

class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        int robot_state = 1; // 机器人的方向
        int robot_x = 0, robot_y = 0; // 机器人坐标
        int dirs[4][2]{ { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
        unordered_set<int> obstacles_map; // 障碍物
        for (const auto& obstacle : obstacles) {
            obstacles_map.emplace(obstacle[0] * 60001 + obstacle[1]); // 0 <= obstacles.length <= 10^4 -3 * 104 <= xi, yi <= 3 * 104
        }
        int res = 0;
        for (const auto& command : commands) {
            if (command < 0) { // 转向
                robot_state += command == -1 ? 1 : -1;
                robot_state %= 4;
                if (robot_state < 0) {
                    robot_state += 4;
                }
            }
            else {
                for (int i = 0; i < command; ++i) {
                    if (obstacles_map.count((robot_x + dirs[robot_state][0]) * 60001 \
                        + robot_y + dirs[robot_state][1])) {
                        break;
                    }
                    robot_x += dirs[robot_state][0];
                    robot_y += dirs[robot_state][1];
                    res = max(res, robot_x * robot_x + robot_y * robot_y);
                }
            }
        }
        return res;
    }
};

class Solution2 {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        int dirs[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
        int px = 0, py = 0, d = 1;
        unordered_set<int> mp;
        for (auto& obstacle : obstacles) {
            mp.emplace(obstacle[0] * 60001 + obstacle[1]);
        }
        int res = 0;
        for (int c : commands) {
            if (c < 0) {
                d += c == -1 ? 1 : -1;
                d %= 4;
                if (d < 0) {
                    d += 4;
                }
            }
            else {
                for (int i = 0; i < c; i++) {
                    if (mp.count((px + dirs[d][0]) * 60001 + py + dirs[d][1])) {
                        break;
                    }
                    px += dirs[d][0];
                    py += dirs[d][1];
                    res = max(res, px * px + py * py);
                }
            }
        }
        return res;
    }
};


int main() {
    // ：commands = [4,-1,4,-2,4], obstacles = [[2,4]]
    auto commands = vector<int>{ 4, -1, 4, -2, 4 };
    auto obstacles = vector<vector<int>>{ { 2, 4 } };
    Solution s;
    cout << s.robotSim(commands, obstacles);
    return 0;
}
