#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    int minStoneSum(vector<int>& piles, int k) {
        priority_queue<int> heap(piles.begin(), piles.end());
        int res = accumulate(piles.begin(), piles.end(), 0);
        while (k--) {
            int t = heap.top();
            res -= t / 2;
            heap.pop();
            heap.push((t + 1) / 2);
        }
        return res;
    }
};

int main() {
    // piles = [5,4,9], k = 2
    // vector<int> piles {5, 4, 9};
    // int k = 2;
    vector<int> piles {4, 3, 6, 7};
    int k = 3;
    cout << Solution().minStoneSum(piles, k) << endl;
    return 0;
}