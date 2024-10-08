#include "../../head_file.h"

/*
problme: 2034. 股票价格波动

给你一支股票价格的数据流。数据流中每一条记录包含一个 时间戳 和该时间点股票对应的 价格 。

不巧的是，由于股票市场内在的波动性，股票价格记录可能不是按时间顺序到来的。某些情况下，有的记录可能是错的。如果两个有相同时间戳的记录出现在数据流中，前一条记录视为错误记录，后出现的记录 更正 前一条错误的记录。

请你设计一个算法，实现：

    更新 股票在某一时间戳的股票价格，如果有之前同一时间戳的价格，这一操作将 更正 之前的错误价格。
    找到当前记录里 最新股票价格 。最新股票价格 定义为时间戳最晚的股票价格。
    找到当前记录里股票的 最高价格 。
    找到当前记录里股票的 最低价格 。

请你实现 StockPrice 类：

    StockPrice() 初始化对象，当前无股票价格记录。
    void update(int timestamp, int price) 在时间点 timestamp 更新股票价格为 price 。
    int current() 返回股票 最新价格 。
    int maximum() 返回股票 最高价格 。
    int minimum() 返回股票 最低价格 。

示例 1：

输入：
["StockPrice", "update", "update", "current", "maximum", "update", "maximum", "update", "minimum"]
[[], [1, 10], [2, 5], [], [], [1, 3], [], [4, 2], []]
输出：
[null, null, null, 5, 10, null, 5, null, 2]

解释：
StockPrice stockPrice = new StockPrice();
stockPrice.update(1, 10); // 时间戳为 [1] ，对应的股票价格为 [10] 。
stockPrice.update(2, 5);  // 时间戳为 [1,2] ，对应的股票价格为 [10,5] 。
stockPrice.current();     // 返回 5 ，最新时间戳为 2 ，对应价格为 5 。
stockPrice.maximum();     // 返回 10 ，最高价格的时间戳为 1 ，价格为 10 。
stockPrice.update(1, 3);  // 之前时间戳为 1 的价格错误，价格更新为 3 。
                          // 时间戳为 [1,2] ，对应股票价格为 [3,5] 。
stockPrice.maximum();     // 返回 5 ，更正后最高价格为 5 。
stockPrice.update(4, 2);  // 时间戳为 [1,2,4] ，对应价格为 [3,5,2] 。
stockPrice.minimum();     // 返回 2 ，最低价格时间戳为 4 ，价格为 2 。


提示：

    1 <= timestamp, price <= 109
    update，current，maximum 和 minimum 总 调用次数不超过 105 。
    current，maximum 和 minimum 被调用时，update 操作 至少 已经被调用过 一次 。

url: https://leetcode.cn/problems/stock-price-fluctuation/description/
 */

// time complexity: O()
// spatial complexity: O()
class StockPrice1 {
public:
    StockPrice1() {

    }

    void update(int timestamp, int price) {
        if (mp.count(timestamp)) {
            s.erase(mp[timestamp]);
        }
        s.emplace(price);
        mp[timestamp] = price;
        now_price = price;
    }

    int current() {
        return now_price;
    }

    int maximum() {
        return *s.rbegin();
    }

    int minimum() {
        return *s.begin();
    }
    map<int, int> mp; // timestamp : price
    set<int> s; // price
    int now_price;
};

class StockPrice2 {
public:
    StockPrice2() {
        this->max_stamp = 0;
    }

    void update(int timestamp, int price) {
        max_stamp = max(max_stamp, timestamp);
        mp[timestamp] = price;
        min_heap.emplace(timestamp, price);
        max_heap.emplace(timestamp, price);
    }

    int current() {
        return mp[max_stamp]; // 最新股票价格 定义为时间戳最晚的股票价格
    }

    int maximum() {
        while (true) {
            auto [stamp, p] = max_heap.top();
            // int stamp = max_heap.top().first, p = max_heap.top().second;
            if (mp[stamp] == p) {
                return p;
            }
            max_heap.pop(); // mp[stamp] !=  p , stamp 是重复值
        }
    }

    int minimum() {
        while (true) {
            int stamp = min_heap.top().first, p = min_heap.top().second;
            if (mp[stamp] == p) {
                return p;
            }
            min_heap.pop();
        }
    }
    int max_stamp;
    unordered_map<int, int> mp;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
    priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>> max_heap;
};

typedef pair<int,int> pii;

class StockPrice {
public:
    StockPrice() {
        this->maxTimestamp = 0;
    }
    
    void update(int timestamp, int price) {
        maxTimestamp = max(maxTimestamp, timestamp);
        timePriceMap[timestamp] = price;
        pqMax.emplace(price, timestamp);
        pqMin.emplace(price, timestamp);
    }
    
    int current() {
        return timePriceMap[maxTimestamp];
    }
    
    int maximum() {
        while (true) {
            int price = pqMax.top().first, timestamp = pqMax.top().second;
            if (timePriceMap[timestamp] == price) {
                return price;
            }
            pqMax.pop();
        }
    }
    
    int minimum() {
        while (true) {
            int price = pqMin.top().first, timestamp = pqMin.top().second;
            if (timePriceMap[timestamp] == price) {
                return price;
            }
            pqMin.pop();
        }
    }
private:
    int maxTimestamp;
    unordered_map<int, int> timePriceMap;
    priority_queue<pii, vector<pii>, less<pii>> pqMax;
    priority_queue<pii, vector<pii>, greater<pii>> pqMin;
};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */

int main() {

    return 0;
}