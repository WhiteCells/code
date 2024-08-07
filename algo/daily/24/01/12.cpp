#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/construct-string-with-repeat-limit
 */

class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        unordered_map<char, int> counter;
        for (const auto &c : s) {
            ++counter[c];
        }
        priority_queue<pair<char, int>> heap;
        for (auto &[ch, cnt] : counter) {
            heap.push(make_pair(ch, cnt));
        }
        char pre = ' ';
        int cnt = 0;
        string res;
        while (!heap.empty()) {
            auto t = heap.top();
            heap.pop();
            if (t.first == pre) {
                if (t.second < repeatLimit) {
                    res += t.first;
                    ++cnt;
                    --t.second;
                } else {
                    if (!heap.empty()) {
                        auto t2 = heap.top();
                        heap.pop();
                        pre = t2.first;
                        cnt = 1;
                        --t2.second;
                        res += t2.first;
                        if (t2.second) {
                            heap.push(t2);
                        }
                    } else {
                        break;
                    }
                }
            } else {
                pre = t.first;
                cnt = 1;
                --t.second;
                res += t.first;
            }
            if (t.second) {
                heap.push(t);
            }
        }
        return res;
    }
};

int main() {
    string s = "cczazcc";
    int repeatLimit = 3;
    cout << Solution().repeatLimitedString(s, repeatLimit) << endl;
    return 0;
}