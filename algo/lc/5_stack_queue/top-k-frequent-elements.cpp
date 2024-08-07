#include "D:\distake\Coding\head_file.h"

class Solution {
public:
    class mycompare {
    public:
        bool operator()(const pair<int, int>& left, const pair<int, int>& right) {
            return left.second > right.second; // 大顶堆
        }
    };
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 统计每个数字出现次数
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); ++i) {
            map[nums[i]]++;
        }
        // 优先队列，vector 作为底层，mycompare 作为队列排序的方式
        priority_queue<pair<int, int>, vector<pair<int, int>>, mycompare> pri_que;
        for (auto iter = map.begin(); iter != map.end(); ++iter) {
            pri_que.push(*iter);
            if (pri_que.size() > k) {
                pri_que.pop();
            }
        }
        vector<int> rev;
        for (int i = 0; i < k; ++i) {
            rev.push_back(pri_que.top().first);
            pri_que.pop();
        }
        return rev;
    }
};

int main() {
    Solution s;
    vector<int> nums { 1, 1, 1, 2, 2, 3, 5, 5, 1 };
    vector<int> rev = s.topKFrequent(nums, 3);
    for (auto& x : rev) {
        cout << x << " ";
    }
    return 0;
}