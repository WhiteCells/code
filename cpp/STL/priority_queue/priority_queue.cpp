#include <iostream>
#include <vector>
#include <functional>

#include <queue> // 包含 priority_queue

// 优先队列，本质是堆实现。与队列不同的是，priority_queue只能访问队列头部的信息（使用top），且插入元素后，会自动排序。

// template<
//     class T,
//     class Container = std::vector<T>,
//     class Compare = std::less<typename Container::value_type>
// > class priority_queue;

// T 与 Container::value_type 需要相同，

void UsePriorityQueue() {
    std::priority_queue<int> q;

    q.push(1); // 队尾插入元素，并排序（降序）
    q.push(5);
    q.push(4);
    q.push(2);
    q.push(7);
    q.emplace(6); // 原地构建一个元素并插入队尾

    std::cout << "q.size() = " << q.size() << '\n'; // priority_queue 长度

    q.pop(); // 弹出队头 7
    while (!q.empty()) {
        std::cout << q.top() << ' '; // 弹出队头
        q.pop();
    }
    std::cout << '\n';
}

// 默认就是大顶堆
void MaxHeap() {
    std::priority_queue<int, std::vector<int>, std::less<int>> max_heap;
    max_heap.push(4);
    max_heap.push(3);
    max_heap.push(1);
    max_heap.push(2);

    while (!max_heap.empty()) {
        std::cout << max_heap.top() << ' ';
        max_heap.pop();
    }
    std::cout << '\n'; // 4 3 2 1
}

void MinHeap() {
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
    min_heap.push(4);
    min_heap.push(3);
    min_heap.push(1);
    min_heap.push(2);

    while (!min_heap.empty()) {
        std::cout << min_heap.top() << ' ';
        min_heap.pop();
    }
    std::cout << '\n'; // 1 2 3 4
}

void LamdaAsAComparisonFunction() {
    // std::function<bool(const std::pair<int, int>, const std::pair<int, int>)> cmp = [&](const std::pair<int, int>& left, const std::pair<int, int>& right) {
    auto cmp = [&](const std::pair<int, int>& left, const std::pair<int, int>& right) {
        return left.second > right.second;
    };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> q(cmp);
    q.push(std::make_pair(1, 2));
}

int main() {
    UsePriorityQueue();
    // MaxHeap();
    // MinHeap();
    return 0;
}