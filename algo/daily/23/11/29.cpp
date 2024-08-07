#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/smallest-number-in-infinite-set/
 */

class SmallestInfiniteSet {
public:
    SmallestInfiniteSet() {

    }

    int popSmallest() {
        while (s.count(small)) {
            ++small;
        }
        s.insert(small);
        return small;
    }

    void addBack(int num) {
        if (s.count(num)) {
            if (num < small) {
                small = num;
            }
            s.erase(num);
        }
    }
private:
    // 记录被移除的元素
    set<int> s;
    int small = 1;
};

class SmallestInfiniteSet2 {
public:
    SmallestInfiniteSet2() : mp(1001) {

    }

    int popSmallest() {
        // while (s.count(small)) {
        while (mp[small]) {
            ++small;
        }
        // s.insert(small);
        mp[small] = 1;
        return small;
    }

    void addBack(int num) {
        // if (s.count(num)) {
        if (mp[num]) {
            if (num < small) {
                small = num;
            }
            // s.erase(num);
            mp[num] = 0;
        }
    }
private:
    // 记录被移除的元素
    // set<int> s;
    vector<int> mp;
    int small = 1;
};

/*
["SmallestInfiniteSet","addBack"]
[[],[870]]
 */

int main() {
    SmallestInfiniteSet2 si;
    // si.addBack(2);
    // cout << si.popSmallest() << endl;
    // cout << si.popSmallest() << endl;
    // cout << si.popSmallest() << endl;
    // si.addBack(1);
    // cout << si.popSmallest() << endl;
    // cout << si.popSmallest() << endl;
    // cout << si.popSmallest() << endl;

    si.addBack(870);
    return 0;
}