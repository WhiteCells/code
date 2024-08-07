#include <iostream>
#include <vector>
#include <algorithm>
using  namespace std;

// 输入：nums = [-1,2,1,-4], target = 1
// 输出：2
// 解释：与 target 最接近的和是 2 (-1 + 2 + 1 = 2) 。

// -4 -1 1 2

class Solution {
public:
	int threeSumClosest(vector<int>& nums, int target) {
		int distance = INT_MAX, n = nums.size(), ans;
		sort(nums.begin(), nums.end());
		for (int i = 0; i < n; ++i) {
			// if (i > 0 && nums[i] == nums[i - 1]) {
			// 	continue;
			// }
			int left = i + 1, right = n - 1;
			int one_num = nums[i];
			while (left < right) {
				// if (left == i + 1 && nums[left] == nums[left - 1]) {
				// 	++left;
				// 	continue;
				// }
				int sum = one_num + nums[left] + nums[right]; // 当前总和
				if (abs(target - sum) < abs(distance)) {
					distance = abs(target - sum);
					ans = sum;
				}
				if (sum > target) {
					--right;
				}
				else if (sum < target) {
					++left;
				}
				else {
					return sum;
				}
			}
		}
		return ans;
	}
};

int main() {
	// vector<int> nums{ -1, 1, 2, -4 };
	vector<int> nums{ 0, 0, 0 };
	int target = 1;
	Solution s;
	cout << s.threeSumClosest(nums, target);
	return 0;
}