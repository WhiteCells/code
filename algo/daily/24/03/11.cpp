#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    string capitalizeTitle(string title) {
        for (int i = 0; i < title.size(); ++i) {
            int j = i;
            for (; title[j] != ' ' && j < title.size(); ++j) {
            }
            if (j - i > 2) {
                title[i++] &= 95;
            }
            while (i < j) {
                title[i++] |= 32;
            }
        }
        return title;
    }
};

int main() {
    cout << Solution().capitalizeTitle("L hV") << endl;
    return 0;
}