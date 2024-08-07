#include <iostream> 
#include <vector>
#include <queue>
#include <functional>

using namespace std;

class Solution {
public:
    using PII = pair<int, int>;
    int findCrossingTime(int n, int k, vector<vector<int>>& time) {

        // time[i] = [leftToRighti, pickOldi, rightToLefti, putNewi]
        // 过河耗时越高，
        auto Cmp = [&](int x, int y) {
            int time_x = time[x][0] + time[x][2];
            int time_y = time[y][0] + time[y][2];
            return time_x == time_y ? x < y /*下标大优先级高*/ : time_x < time_y /*耗时多优先级高*/;
            };

        priority_queue<int, vector<int>, decltype(Cmp)> left_wait(Cmp), right_wait(Cmp);
        priority_queue<PII, vector<PII>, greater<PII>> left_work, right_work;

        int box_num = n, cur_time = 0;

        // 员工刚开始全部在左侧等待
        for (int i = 0; i < k; ++i) {
            left_wait.push(i);
        }

        // 旧仓库还有箱子，或者右侧还有人就继续
        while (box_num > 0 || !right_work.empty() || !right_wait.empty()) {

            // 员工从工作到等待
            while (!left_work.empty() && left_work.top().first <= cur_time) {
                left_wait.push(left_work.top().second);
                left_work.pop();
            }

            while (!right_work.empty() && right_work.top().first <= cur_time) {
                right_wait.push(right_work.top().second); // 拿箱子需要的时间
                right_work.pop(); // 弹出工作到等待的员工
            }

            // 右侧有员工等待，取出右侧优先级最低的员工过桥
            // 右岸 ====》 左岸
            if (!right_wait.empty()) {
                int id = right_wait.top();
                right_wait.pop();
                cur_time += time[id][2]; // 过河耗时
                left_work.push({ cur_time + time[id][3], id }); // 到左侧工作
            }
            // 右侧还有箱子，且左侧有人在等待，取出左侧优先级最低的员工过桥
            // 左岸 ====》 右岸
            else if (box_num > 0 && !left_wait.empty()) {
                int id = left_wait.top();
                left_wait.pop();
                cur_time += time[id][0]; // 过河耗时
                right_work.push({ cur_time + time[id][1], id }); // 到右侧工作
                --box_num;
            }
            // 没有人需要过桥
            else {
                int next_time = INT_MAX;
                if (!left_work.empty()) {
                    next_time = min(next_time, left_work.top().first);
                }
                if (!right_work.empty()) {
                    next_time = min(next_time, right_work.top().first);
                }
                if (next_time != INT_MAX) {
                    cur_time = max(cur_time, next_time);
                }
            }
        }
        return cur_time;
    }
};

int main() {
    Solution s;
    vector<vector<int>> time{
        { 1, 1, 2, 1 },
        { 1, 1, 3, 1 },
        { 1, 1, 4, 1 },
        { 1, 1, 4, 2 }
    };
    cout << s.findCrossingTime(1, 3, time);
    return 0;
}