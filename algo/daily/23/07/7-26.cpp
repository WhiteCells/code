#include <iostream>
#include <vector>
#include <bitset>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {

        // 操作类型 1 为 queries[i] = [1, l, r] 。你需要将 nums1 从下标 l 到下标 r 的所有 0 反转成 1 或将 1 反转成 0 。l 和 r 下标都从 0 开始。
        // 操作类型 2 为 queries[i] = [2, p, 0] 。对于 0 <= i < n 中的所有下标，令 nums2[i] = nums2[i] + nums1[i] * p 。
        // 操作类型 3 为 queries[i] = [3, 0, 0] 。求 nums2 中所有元素的和。
        vector<long long> ans;
        int cnt = 0;
        long long sum = 0;
        for (int i = 0; i < nums2.size(); ++i) {
            sum += nums2[i];
            if (nums1[i]) {
                ++cnt;
            }
        }
        for (const auto& querie : queries) {
            if (1 == querie[0]) {
                for (int i = querie[1]; i <= querie[2]; ++i) {
                    nums1[i] = !nums1[i];
                    if (nums1[i]) {
                        ++cnt;
                    }
                    else {
                        --cnt;
                    }
                }
            }
            else if (2 == querie[0]) {
                sum += cnt * querie[1];
            }
            else {
                ans.push_back(sum);
            }
        }
        return ans;
    }
};



typedef long long ll;

class SegmentTree1 {
private:
    struct SegmentTreeNode {
        ll tl;
        ll tr;
        ll s;
        int lazy;
    };
    vector<SegmentTreeNode> st;

public:
    inline void push_down(ll index) {
        st[index << 1].lazy ^= 1;
        st[index << 1 | 1].lazy ^= 1;
        st[index << 1].s = st[index << 1].tr - st[index << 1].tl + 1 - st[index << 1].s;
        st[index << 1 | 1].s = st[index << 1 | 1].tr - st[index << 1 | 1].tl + 1 - st[index << 1 | 1].s;
        st[index].lazy = 0;
    }

    inline void push_up(ll index) {
        st[index].s = st[index << 1].s + st[index << 1 | 1].s;
    }

    SegmentTree1(vector<int>& init_list) { // 用init_list初始化
        st = vector<SegmentTreeNode>(init_list.size() * 4 + 10);
        build(init_list, 1, init_list.size());
    }

    void build(vector<int>& init_list, ll l, ll r, ll index = 1) { // 建树
        st[index].tl = l;
        st[index].tr = r;
        st[index].lazy = 0;
        if (l == r) {
            st[index].s = init_list[l - 1];
        }
        else {
            ll mid = (l + r) >> 1;
            build(init_list, l, mid, index << 1);
            build(init_list, mid + 1, r, index << 1 | 1);
            push_up(index);
        }
    }

    void flip(ll l, ll r, ll index = 1) {//区间翻转
        if (l > st[index].tr or r < st[index].tl)
            return;
        else if (l <= st[index].tl and st[index].tr <= r) {
            st[index].s = st[index].tr - st[index].tl + 1 - st[index].s;
            st[index].lazy ^= 1;
        }
        else {
            if (st[index].lazy)
                push_down(index);
            flip(l, r, index << 1);
            flip(l, r, index << 1 | 1);
            push_up(index);
        }
    }

    ll query(ll l, ll r, ll index = 1) {//区间求和
        if (l <= st[index].tl and st[index].tr <= r) {
            return st[index].s;
        }
        else {
            if (st[index].lazy)
                push_down(index);
            if (r <= st[index << 1].tr)
                return query(l, r, index << 1);
            else if (l > st[index << 1].tr)
                return query(l, r, index << 1 | 1);
            return query(l, r, index << 1) + query(l, r, index << 1 | 1);
        }
    }
};


class Solution2 {
public:
    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        vector<ll> res;
        SegmentTree1 tree(nums1);
        ll s = accumulate(nums2.begin(), nums2.end(), 0LL);
        for (int i = 0; i < queries.size(); i++) {
            auto& qi = queries[i];
            if (qi[0] == 1)
                tree.flip(qi[1] + 1, qi[2] + 1);
            else if (qi[0] == 2)
                s += tree.query(1, nums1.size()) * qi[1];
            else
                res.push_back(s);
        }
        return res;
    }
};


using ll = long long;
class SegmentTree {
private:
    struct SegmentTreeNode {
        ll _left;
        ll _right;
        ll _sum;
        int lazy;
    };
    vector<SegmentTreeNode> st;

public:
    // 向上整合
    void PushUp(ll index) {
        st[index << 1].lazy ^= 1;
    }
    // 向下整合
    void PushDown(ll index) {

    }
    // 构造
    SegmentTree(vector<int>& init_list) {

    }
    // 建树
    void Build(vector<int>& init_list, ll left, ll right, ll index = 1) {

    }
    // 区间翻转
    void Flip(ll left, ll right, ll index = 1) {

    }
    // 区间求和
    ll Query(ll left, ll right, ll index = 1) {

    }
};

class Solution3 {
public:
    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        vector<ll> res;
        SegmentTree tree(nums1);
        ll sum = 0;
        for (const auto& num : nums1) {
            sum += num;
        }
        for (const auto& querie : queries) {
            if (0 == querie[0]) {
                tree.Flip(querie[1] + 1, querie[2] + 1);
            }
            else if (1 == querie[1]) {
                sum += tree.Query(1, nums1.size() * querie[1]);
            }
            else {
                res.push_back(sum);
            }
        }
        return res;
    }
};

int main() {
    // Solution2 s;
    // vector<int> nums1{}, nums2{};
    // vector<vector<int>> queries{ {} };
    // auto res = s.handleQuery(nums1, nums2, queries);

    return 0;
}