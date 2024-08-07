#include <iostream>

using namespace std;

class Solution {
public:
    string addStrings(string num1, string num2) {
        int i = num1.size() - 1;
        int j = num2.size() - 1;
        string ans;
        int remain = 0; // 进位
        while (i >= 0 | j >= 0 | remain) {
            int n1 = i >= 0 ? num1[i] - '0' : 0;
            int n2 = j >= 0 ? num2[j] - '0' : 0;
            int sum = n1 + n2 + remain;
            ans.push_back(sum % 10 + '0');
            remain = sum / 10;
            i = i >= 0 ? i - 1 : i;
            j = j >= 0 ? j - 1 : j;
        }
        int right = ans.size() - 1;
        for (int left = 0; left < right; ++left, --right) {
            char tmp = ans[left];
            ans[left] = ans[right];
            ans[right] = tmp;
        }
        return ans;
    }
};


int main() {
    string num1 = "9";
    string num2 = "99";
    Solution s;
    cout << s.addStrings(num1, num2);
    return 0;
}