#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        auto cmp = [&](auto& v1, auto& v2) {
            return v1[1] - v1[0] < v2[1] - v2[0];
        };
        sort(intervals.begin(), intervals.end(), cmp);
        int n = intervals.size();
        vector<int> ans(n, -1);
        set<pair<int, int>> st;
        for (int i = 0; i < n; ++i) {
            st.emplace(queries[i], i);
        }
        for (auto& v : intervals) {
            auto it = st.lower_bound({ v[0], -1 });
            while (it != st.end() && it->first <= v[1]) {
                ans[it->second] = v[1] - v[0] + 1, st.erase(it++);
            }
        }
        return ans;
    }
};

class Solution2 {
public:
    vector<int> minInterval(vector<vector<int>>& itv, vector<int>& q) {
        int n = q.size();
        vector<int> ans(n, -1);
        set<pair<int, int>> st;
        for (int i = 0; i < n; ++i) st.emplace(q[i], i);
        sort(itv.begin(), itv.end(), [&](const auto& a, const auto& b) {return a[1] - a[0] < b[1] - b[0];});
        for (auto& v : itv) {
            auto it = st.lower_bound({ v[0], -1 });
            while (it != st.end() && it->first <= v[1]) {
                ans[it->second] = v[1] - v[0] + 1, st.erase(it++);
            }
        }
        return ans;
    }
};

int main() {
    auto v1 = vector<vector<int>>{ { 1, 4 }, { 2, 4 }, { 3, 6 }, { 4, 4 } };
    auto v2 = vector<int>{ 2, 3, 4, 5 };
    Solution s;
    auto ans = s.minInterval(v1, v2);
    for (auto& val : ans) {
        cout << val << " ";
    }
    return 0;
}