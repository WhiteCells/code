#include "D:/distake/Coding/head_file.h"


class Solution {
private:
    vector<string> res;
    unordered_map<string, map<string, int>> targets; // [起点, [终点, 航班次数]]，终点能不能去只需要标记一下航班次数就可以
    // unordered_map<string, multiset<string>> unmap; // 不使用的原因是，终点集合需要进行删除，但是删除之后迭代器就会失效
    bool dfs(int ticketNum) {
        if (ticketNum == res.size()) {
            return true;
        }
        for (pair<const string, int>& target : targets[res[res.size() - 1]]) {
            if (target.second > 0) { // 机场未飞过
                res.push_back(target.first);
                --target.second;
                dfs(ticketNum); 
                ++target.second;
                res.pop_back();
            }
        }
    }
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (const auto& ticket : tickets) {
            targets[ticket[0]][ticket[1]]++; // 记录映射关系
        }
        res.push_back("JFK");
        dfs(tickets.size());
        return res;
    }
};


int main() {
    Solution s;

    return 0;
}