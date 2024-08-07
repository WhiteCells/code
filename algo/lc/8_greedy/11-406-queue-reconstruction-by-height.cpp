#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-05-24 18:53:24
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-05-24 18:53:24
 * @Description: 406. 根据身高重建队列
 * https://leetcode.cn/problems/queue-reconstruction-by-height/
 * 输入：people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
 * 输出：         [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
 * 输入：people = [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]]
 * 输出：         [[4,0],[5,0],[2,2],[3,2],[1,4],[6,0]]
*/

class Solution {
private:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        if (a[0] == b[0]) {
            return a[1] < b[1]; // h 相等，就按照 k 递增
        }
        return a[0] > b[0]; // h 递减
    }
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), cmp);
        vector<vector<int>> res; // 结果容器
        for (int i = 0; i < people.size(); ++i) {
            res.insert(res.begin() + people[i][1], people[i]);
        }
        return res;
    }
};

class Solution2 {
private:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        if (a[0] == b[0]) {
            return a[1] < b[1]; // h 相等，按照 k 递增
        }
        return a[0] > b[0]; // h 递减
    }
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), cmp);
        list<vector<int>> res;
        for (int i = 0; i < people.size(); ++i) {
            auto iter = res.begin();
            int index = people[i][1];
            while (index--) { // 找插入下标的迭代器
                iter++;
            }
            res.insert(iter, people[i]);
        }
        return vector<vector<int>>(res.begin(), res.end());
    }
};


int main() {
    Solution s;
    vector<vector<int>> people {{7, 0}, { 4, 4 }, { 7, 1 }, { 5, 0 }, { 6, 1 }, { 5, 2 }};
    vector<vector<int>> res = s.reconstructQueue(people);
    for (auto& v : res) {
        for (auto& val : v) {
            cout << val << " ";
        }
        cout << '\n';
    }
    return 0;
}