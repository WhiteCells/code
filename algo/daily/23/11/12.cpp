#include "../../head_file.h"

/*
problme:

url:
 */

// time complexity: O()
// spatial complexity: O()
class RangeModule {
public:
    RangeModule() {
        
    }

    void addRange(int left, int right) {
        auto it = m.upper_bound(left);
        if (it != m.begin()) {
            auto start = prev(it);
            if (start->second >= right) {
                return;
            } else if (start->second >= left) {
                left = start->first;
                m.erase(start);
            }
        }
        while (it != m.end() && it->first <= right) {
            right = max(right, it->second);
            it = m.erase(it);
        }
        m[left] = right;
    }

    bool queryRange(int left, int right) {
        auto it = m.upper_bound(left);
        if (it == m.begin()) {
            return false;
        }
        it = prev(it);
        return right <= it->second;
    }

    void removeRange(int left, int right) {
        auto it = m.upper_bound(left);
        if (it != m.begin()) {
            auto start = prev(it);
            if (start->second >= right) {
                int r = start->second;
                if (start->first == left) {
                    m.erase(start);
                } else {
                    start->second = left;
                }
                if (right != r) {
                    m[right] = r;
                }
                return;
            } else if (start->second > left) {
                if (start->first == left) {
                    m.erase(start);
                } else {
                    start->second = left;
                }
            }
        }
        while (it != m.end() && it->first < right) {
            if (it->second <= right) {
                it = m.erase(it);
            } else {
                m[right] = it->second;
                m.erase(it);
                break;
            }
        }
    }
private:
    map<int, int> m;
};

int main() {
    RangeModule rm;
    rm.addRange(10, 20);
    rm.removeRange(14, 16);
    cout << rm.queryRange(10, 14) << endl;
    cout << rm.queryRange(13, 15) << endl;
    cout << rm.queryRange(16, 17) << endl;
    return 0;
}