#include "../../head_file.h"

/*
problme: 

url: 
 */

class BinaryIndexTree {
public:
    BinaryIndexTree(int n) : tree(n + 1) {

    }

    void add(int i) {
        while (i < tree.size()) {
            tree[i] += 1;
            i += i & -i;
        }
    }

    int get(int i) {
        int res = 0;
        while (i > 0) {
            res += tree[i];
            i &= i - 1;
        }
        return res;
    }

private:
    vector<int> tree;
};

class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> sorted_nums = nums;
        sort(sorted_nums.begin(), sorted_nums.end());
        unordered_map<int, int> index;
        for (int i = 0; i < n; ++i) {
            index[sorted_nums[i]] = i + 1;
        }

        vector<int> arr1 { nums[0] };
        vector<int> arr2 { nums[1] };
        
        BinaryIndexTree tree1(n);
        BinaryIndexTree tree2(n);
        tree1.add(index[nums[0]]);
        tree2.add(index[nums[1]]);
        
        for (int i = 2; i < n; ++i) {
            int cnt1 = arr1.size() - tree1.get(index[nums[i]]);
            int cnt2 = arr2.size() - tree2.get(index[nums[i]]);

            if (cnt1 > cnt2 || (cnt1 == cnt2 && arr1.size() <= arr2.size())) {
                arr1.push_back(nums[i]);
                tree1.add(index[nums[i]]);
            } else {
                arr2.push_back(nums[i]);
                tree2.add(index[nums[i]]);
            }
        }

        arr1.insert(arr1.end(), arr2.begin(), arr2.end());
        return arr1;
    }
};

int main() {
    
    return 0;
}