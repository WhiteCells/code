#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    string removeTrailingZeros(string num) {
        while (num.back() == '0') {
            num.pop_back();
        }
        return num;
    }
};

int main() {
    cout << Solution().removeTrailingZeros("1213000") << endl;
    return 0;
}