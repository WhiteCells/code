// https://leetcode.cn/problems/prime-pairs-with-target-sum/

// 给你一个整数 n 。如果两个整数 x 和 y 满足下述条件，则认为二者形成一个质数对：

//     1 <= x <= y <= n
//     x + y == n
//     x 和 y 都是质数

// 请你以二维有序列表的形式返回符合题目要求的所有 [xi, yi] ，列表需要按 xi 的 非递减顺序 排序。如果不存在符合要求的质数对，则返回一个空数组。

// 注意：质数是大于 1 的自然数，并且只有两个因子，即它本身和 1 。

// 1 <= n <= 10^6

// 输入：n = 10
// 输出：[[3,7],[5,5]]
// 解释：在这个例子中，存在满足条件的两个质数对。 
// 这两个质数对分别是 [3,7] 和 [5,5]，按照题面描述中的方式排序后返回。


// 埃式筛/欧拉筛

#include "../../head_file.h"

// TLE
class Solution1 {
private:
    bool isprime(int x) {
        for (int i = 2; i <= x / i; ++i) {
            if (0 == x % i) {
                return false;
            }
        }
        return true;
    }
public:
    vector<vector<int>> findPrimePairs(int n) {
        map<int, int> mp;
        for (int i = 2; i <= n / 2; ++i) {
            if (isprime(i)) {
                if (isprime(n - i)) {
                    mp.insert(pair<int, int>(i, n - i));
                }
            }
        }
        vector<vector<int>> ans;
        for (auto pair : mp) {
            ans.push_back({ pair.first, pair.second });
        }
        return ans;
    }
};


// 埃氏筛
class Solution2 {
private:
    static const int maxn = 1e6 + 1;
    bitset<maxn> prime;

    void initPrime(int n) {
        for (int i = 2; i <= n / i; ++i) {
            if (!prime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    prime[j] = 1; // 标记并筛除
                }
            }
        }
    }

public:
    vector<vector<int>> findPrimePairs(int n) {
        initPrime(n);
        map<int, int> mp;
        for (int i = 2; i <= n / 2; ++i) {
            if (!prime[i]) {
                if (!prime[n - i]) {
                    mp.insert(make_pair(i, n - i));
                }
            }
        }
        vector<vector<int>> ans;
        for (auto pair : mp) {
            ans.push_back({ pair.first, pair.second });
        }
        return ans;
    }
};


// 欧拉筛
class Solution3 {
private:
    static const int N = 1e6;
    int prime[N] = {};
    int prime_table[N] = {};
    void initPrime(int n) {

    }
public:
    vector<vector<int>> findPrimePairs(int n) {
        for (int i = 2; i <= n; ++i) {

        }
    }
};


int main() {
    // Solution1 s;
    Solution2 s;
    vector<vector<int>> ans = s.findPrimePairs(10);
    for (auto v : ans) {
        for (auto val : v) {
            cout << val << " ";
        }
        cout << '\n';
    }
    return 0;
}