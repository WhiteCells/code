#include "../../head_file.h"

/*
problme:
输入：day = 31, month = 8, year = 2019
输出："Saturday"

输入：day = 18, month = 7, year = 1999
输出："Sunday"

输入：day = 15, month = 8, year = 1993
输出："Sunday"
url:
 */
class Solution {
public:
    string dayOfTheWeek(int day, int month, int year) {
        const char *week[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        int m[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};
        int d = 365 * (year - 1971) + (year - 1969) / 4;
        for (int i = 0; i < month - 1; ++i) {
            d += m[i];
        }
        if ((!(year % 400) || (!(year % 4) && year % 100)) && month >= 3) {
            d += 1;
        }
        d += day;
        return week[(d + 3) % 7];
    }
};

class Solution2 {
public:
    string dayOfTheWeek(int day, int month, int year) {
        vector<string>week = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
        if (month == 1 || month == 2) {
            month += 12;
            --year;
        }
        int K = year % 100;
        int J = year / 100;
        int res = (day + (13 * (month + 1)) / 5 + K + K / 4 + J / 4 - 2 *J) % 7;
        return week[(res + 7) % 7];
    }
};


int main() {
    // cout << Solution().dayOfTheWeek(1, 1, 2019) << endl;
    // cout << Solution().dayOfTheWeek(31, 8, 2019) << endl;
    // cout << Solution().dayOfTheWeek(18, 7, 1999) << endl;
    // cout << Solution().dayOfTheWeek(15, 8, 1993) << endl;

    // cout << Solution2().dayOfTheWeek(1, 1, 2019) << endl;
    // cout << Solution2().dayOfTheWeek(31, 8, 2019) << endl;
    // cout << Solution2().dayOfTheWeek(18, 7, 1999) << endl;
    // cout << Solution2().dayOfTheWeek(15, 8, 1993) << endl;

    return 0;
}