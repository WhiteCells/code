#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    bool isAcronym(vector<string>& words, string s) {
        if (s.size() > words.size()) {
            return false;
        }
        for (int i = 0; i < words.size(); ++i) {
            if (words[i][0] != s[i]) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    
    return 0;
}