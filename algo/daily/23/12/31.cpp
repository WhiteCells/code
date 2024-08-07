#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    int dayOfYear(string date) {
        vector<int> month {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int y = getDate(date, 0, 4), m = getDate(date, 5, 7), d = getDate(date, 8, 10);
        for (int i = 1; i < m; ++i) {
            d += month[i - 1];
        }
        if (m > 2 && (!(y % 400) || (!(y % 4) && y % 100))) {
            d += 1;
        }
        return d;
    }
private:
    int getDate(string &date, int s, int e) {
        int res = 0;
        for (int i = s; i < e; ++i) {
            res = res * 10 + (date[i] - '0');
        }
        return res;
    }
};

int main() {
    cout << Solution().dayOfYear("2004-03-01") << endl;
    return 0;
}