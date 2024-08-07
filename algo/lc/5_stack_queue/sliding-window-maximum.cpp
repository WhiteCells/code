#include "D:\distake\Coding\head_file.h"

class Solution1 {
public:
    // 单调队列的封装
    class MyQueue {
    public:
        // 单调队列的数据压入队尾
        void push_back(int val) {
            while (!deq.empty() && val > deq.back()) {
                deq.pop_back();
            }
            deq.push_back(val);
        }
        // 单调队列删除队头
        void pop_front(int val) {
            if (!deq.empty() && val == deq.front()) {
                deq.pop_front();
            }
        }
        // 返回单调队列的队头
        int front() {
            return deq.front();
        }
        deque<int> deq;
    };
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MyQueue que;
        for (int i = 0; i < k; ++i) {
            que.push_back(nums[i]);
        }
        vector<int> rev;
        rev.push_back(que.front());

        for (int i = k; i < nums.size(); ++i) {
            que.pop_front(nums[i - k]);
            que.push_back(nums[i]);
            rev.push_back(que.front());
        }
        return rev;
    }
};

class Solution2 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> deq; // deque 来做单调队列，方便头删和尾删
        vector<int> rev; // 结果容器

        // 先将前 k 个数放进单调队列
        // 这里是维护一个单调递减的队列
        for (int i = 0; i < k; ++i) {
            // 当入队元素大于队列队尾的时候就弹出队尾，直到 入队元素小于队尾 或者 队列为空
            while (!deq.empty() && deq.back() < nums[i]) {
                deq.pop_back();
            }
            // 然后元素入队
            deq.push_back(nums[i]);
        }

        // 现在的队头就是满足第一个窗口中的最大值
        rev.push_back(deq.front()); // 将其放入结果容器

        // 剩下的元素从 （k + 1）(逻辑下标，下面写的是物理下标) 个开始入队
        for (int i = k; i < nums.size(); ++i) {
            // nums[i - k] 代表 nums 容器在滑动窗口里的第一个元素
            // 如果这个元素和队头相等说明这次移动窗口的时候这个元素就不应该在窗口内，应该弹出
            if (deq.front() == nums[i - k]) {
                deq.pop_front();
            }
            // 维护单调队列
            // 当入队元素比队尾大的时候弹出队尾，直到 入队元素比队尾小 或者 队列为空
            while (!deq.empty() && deq.back() < nums[i]) {
                deq.pop_back();
            }
            deq.push_back(nums[i]); // while执行后满足条件，元素入队

            rev.push_back(deq.front()); // 队头就是当前窗口的最大值
        }
        return rev;
    }
};

// class Solution {
// private:
//     class MyQueue { //单调队列（从大到小）
//     public:
//         deque<int> que; // 使用deque来实现单调队列
//         // 每次弹出的时候，比较当前要弹出的数值是否等于队列出口元素的数值，如果相等则弹出。
//         // 同时pop之前判断队列当前是否为空。
//         void pop(int value) {
//             if (!que.empty() && value == que.front()) {
//                 que.pop_front();
//             }
//         }
//         // 如果push的数值大于入口元素的数值，那么就将队列后端的数值弹出，直到push的数值小于等于队列入口元素的数值为止。
//         // 这样就保持了队列里的数值是单调从大到小的了。
//         void push(int value) {
//             while (!que.empty() && value > que.back()) {
//                 que.pop_back();
//             }
//             que.push_back(value);

//         }
//         // 查询当前队列里的最大值 直接返回队列前端也就是front就可以了。
//         int front() {
//             return que.front();
//         }
//     };
// public:
//     vector<int> maxSlidingWindow(vector<int>& nums, int k) {
//         MyQueue que;
//         vector<int> result;
//         for (int i = 0; i < k; i++) { // 先将前k的元素放进队列
//             que.push(nums[i]);
//         }
//         result.push_back(que.front()); // result 记录前k的元素的最大值
//         for (int i = k; i < nums.size(); i++) {
//             que.pop(nums[i - k]); // 滑动窗口移除最前面元素
//             que.push(nums[i]); // 滑动窗口前加入最后面的元素
//             result.push_back(que.front()); // 记录对应的最大值
//         }
//         return result;
//     }
// };

int main() {
    vector<int> v {1, 3, -1, -3, 5, 3, 6, 7};
    // vector<int> v {5, 4, 3, 2, 1};
    Solution2 s;
    vector<int> rev = s.maxSlidingWindow(v, 3);
    for (auto& x : rev) {
        cout << x << " ";
    }
    return 0;
}