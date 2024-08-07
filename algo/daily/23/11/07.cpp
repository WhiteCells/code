#include "../../head_file.h"

/*
problme: 

url: 
 */

// time complexity: O()
// spatial complexity: O()
class Solution {
public:
    int vowelStrings(vector<string>& words, int left, int right) {
        int res = 0;
        for (int i = left; i <= right; ++i) {
            if (isYu(words[i])) {
                ++res;
            }
        }
        return res;
    }

private:
    bool isYu(string& str) {
        return ('a' == str[0] || 'e' == str[0] || 'i' == str[0] || 'o' == str[0] || 'u' == str[0]) && ('a' == str[str.size() - 1] || 'e' == str[str.size() - 1] || 'i' == str[str.size() - 1] || 'o' == str[str.size() - 1] || 'u' == str[str.size() - 1]);  
    }
};


int main() {
    
    return 0;
}