#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	long long maxAlternatingSum(vector<int>& nums) {
		long long ans = 0, sum = 0;
		int n = nums.size(), cnt = 1; // cnt 统计第几个数
		for (int i = 0; i < n; ++i) {
			if (cnt & 1) { // 第奇数个
				sum += nums[i];
			}
			else { // 第偶数个
				sum -= nums[i];
			}
			if (sum <= 0) {
				sum = 0;
				cnt = 1;
				continue;
			}
			++cnt;
			ans = max(ans, sum);
		}
		return ans;
	}
};

class Solution2 {
public:
	long long maxAlternatingSum(vector<int>& nums) {
		long long even = nums[0], odd = 0; // odd 偶数
		int n = nums.size();
		for (int i = 0; i < n; ++i) {
			even = max(even, odd + nums[i]);
			odd = max(odd, even - nums[i]);
		}
		return even;
	}
};

class Solution3 {
public:
	long long maxAlternatingSum(vector<int>& nums) {
		long long ans = 0, pre = 0;
		for (auto num : nums) {
			if (num > pre) {
				ans += num - pre;
			}
			pre = num;
		}
		return ans;
	}
};

int main() {
	// vector<int> nums = { 4, 2, 5, 3 };
	vector<int> nums{ 5, 6, 7, 8 };
	Solution2 s;
	cout << s.maxAlternatingSum(nums);
	return 0;
}