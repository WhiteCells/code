#include "../../head_file.h"

/*
problme:

url:
 */


class Solution {
public:
    int nextBeautifulNumber(int n) {
        for (int i = n + 1; i <= 1224444; ++i) {
            int tmp = i;
            int arr[10] {};
            while (tmp) {
                ++arr[tmp % 10];
                tmp /= 10;
            }
            bool flag = true;
            for (int j = 0; j < 10; ++j) {
                if (arr[j] != 0 && arr[j] != j) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                return i;
            }
        }
        return 0;
    }
};

int main() {
    cout << Solution().nextBeautifulNumber(1) << endl;
    return 0;
}