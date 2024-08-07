#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/count-integers-in-intervals/
 */

// TODO
class CountIntervals {
public:
    CountIntervals() {

    }
    
    void add(int left, int right) {
        auto it = mp.upper_bound(right);
        if (it != mp.begin()) {
            --it;
        }
        while (it != mp.end() && it->first <= right && it->second >= left) {
            int i = it->first, j = it->second;
            left = min(left, i);
            right = max(right, j);
            cnt -= j - i + 1;
            mp.erase(it);
            it = mp.upper_bound(right);
            if (it != mp.begin()) {
                --it;
            }
        }
        cnt += right - left + 1;
        mp[left] = right;
    }
    
    int count() {
        return cnt;
    }
private:
    map<int, int> mp;
    int cnt = 0;
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */


int main() {
    
    return 0;
}