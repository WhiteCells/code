#include "../../head_file.h"

/*
problme: 274. H 指数

给你一个整数数组 citations ，其中 citations[i] 表示研究者的第 i 篇论文被引用的次数。计算并返回该研究者的 h 指数。

根据维基百科上 h 指数的定义：h 代表“高引用次数” ，一名科研人员的 h 指数 是指他（她）至少发表了 h 篇论文，并且每篇论文 至少 被引用 h 次。如果 h 有多种可能的值，h 指数 是其中最大的那个。

示例 1：

输入：citations = [3,0,6,1,5]
输出：3
解释：给定数组表示研究者总共有 5 篇论文，每篇论文相应的被引用了 3, 0, 6, 1, 5 次。
     由于研究者有 3 篇论文每篇 至少 被引用了 3 次，其余两篇论文每篇被引用 不多于 3 次，所以她的 h 指数是 3。

示例 2：

输入：citations = [1,3,1]
输出：1


提示：

    n == citations.length
    1 <= n <= 5000
    0 <= citations[i] <= 1000


url: https://leetcode.cn/problems/h-index/description/
 */

class Solution1 {
public:
    int hIndex(vector<int> &citations) {
        int i = citations.size() - 1, h = 0;
        sort(citations.begin(), citations.end());
        while (i >= 0 && citations[i] > h) {
            ++h;
            --i;
        }
        return h;
    }
};

/* 计数排序 */
class Solution2 {
public:
    int hIndex(vector<int> &citations) {
        sort(citations.begin(), citations.end());
        const int n = citations.size();
        int arr[n] {};
        for (int i = 0; i < n; ++i) {
            ++arr[citations[i] > n ? n : citations[i]];
        }
        int cnt = 0;
        for (int i = n; i >= 0; --i) {
            cnt += arr[i];
            if (cnt >= i) {
                return i;
            }
        }
        return 0;
    }
};

/* 二分 */
class Solution3 {
public:
    int hIndex(vector<int> &citations) {
        int i = 0, j = citations.size();
        // 找到一个值 h，有 h 篇论文引用至少 h
        while (i < j) {
            int mid = ((j - i + 1) >> 1) + i;
            int cnt = 0;
            for (int i = 0; i < citations.size(); ++i) {
                if (citations[i] >= mid) {
                    ++cnt;
                }
            }
            if (cnt >= mid) {
                i = mid;
            } else {
                j = mid - 1;
            }
        }
        return i;
    }
};

int main() {
    vector<int> citations { 3, 0, 6, 1, 5 };
    // vector<int> citations { 1, 3, 1 };
    cout << Solution1().hIndex(citations) << endl;
    cout << Solution2().hIndex(citations) << endl;
    cout << Solution3().hIndex(citations) << endl;
    return 0;
}