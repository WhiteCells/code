#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

class Solution {
public:
    int halveArray(vector<int>& nums) {
        auto cmp = [&](const auto& a, const auto& b) {
            return a > b;
        };
        double sum = 0;
        multiset<double, decltype(cmp)> s(cmp);
        for (const auto& num : nums) {
            sum += num;
            s.insert(num);
        }
        double target_sum = sum / 2.0;
        int ans = 0;
        while (target_sum < sum) {
            float val = *s.begin() / 2.0;
            sum -= val;
            s.erase(s.begin());
            s.insert(val);
            ++ans;
        }
        return ans;
    }
};


class Solution2 {
public:
    int halveArray(vector<int>& nums) {
        auto cmp = [&](const auto& a, const auto& b) {
            return a > b;
        };
        sort(nums.begin(), nums.end(), cmp);
        vector<double> v;
        double sum = 0.0;
        for (const auto& num : nums) {
            sum += num;
        }
        double half_sum = sum / 2.0;
        int index1 = 0, index2 = 0, ans = 0, val = 0;
        while (half_sum < sum) {
            if (index2 + 1 > v.size()) {
                val = nums[index1++] / 2.0;
            }
            else {
                val = nums[index1] > v[index2] ? nums[index1++] / 2.0 : v[index2++] / 2.0;
            }
            v.push_back(val);
            sum -= val;
            ++ans;
        }
        return ans;
    }
};

class Solution3 {
public:
    int halveArray(vector<int>& nums) {
        priority_queue<float> q;
        float sum = 0;
        for (const auto& num : nums) {
            sum += num;
            q.push(num);
        }
        float half_sum = sum / 2.0;
        int cnt = 0;
        while (half_sum < sum) {
            sum -= q.top() / 2.0;
            q.push(q.top() / 2.0);
            q.pop();
            ++cnt;
        }
        return cnt;
    }
};

class Solution4 {
public:
    int halveArray(vector<int>& nums) {
        priority_queue<double> q(nums.begin(), nums.end());
        double sum = 0;
        for (const auto& num : nums) {
            sum += num;
            // q.push(num);
        }
        double half_sum = sum / 2.0;
        int cnt = 0;
        while (half_sum < sum) {
            sum -= q.top() / 2.0;
            q.push(q.top() / 2.0);
            q.pop();
            ++cnt;
        }
        return cnt;
    }
};

int main() {
    Solution2 s;
    // auto nums = vector<int>{ 5, 19, 8, 1 };
    // auto nums = vector<int>{
    //     18, 22, 62, 61, 1, 88, 17,
    //     98, 38, 32, 51, 57, 7, 29,
    //     40, 61, 62, 13, 89, 41, 73,
    //     85, 88, 60, 59, 76, 71, 76,
    //     6, 41, 29, 43, 19, 9, 79
    // };

    // auto nums = vector<int>{
    //     18, 22, 62, 61, 1, 88, 17,
    //     98, 38, 32, 51, 57, 7, 29,
    //     40, 61, 62, 13, 89, 41, 73,
    //     85, 88, 60, 59, 76, 71, 76,
    //     76, 41, 29, 43, 19, 9, 79
    // };

    auto nums = vector<int>{
        32, 98, 23, 14, 67, 40, 26, 9, 96,
        96, 91, 76, 4, 40, 42, 2, 31, 13,
        16, 37, 62, 2, 27, 25, 100, 94, 14,
        3, 48, 56, 64, 59, 33, 10, 74, 47,
        73, 72, 89, 69, 15, 79, 22, 18, 53,
        62, 20, 9, 76, 64
    };
    cout << s.halveArray(nums);
    return 0;
}

