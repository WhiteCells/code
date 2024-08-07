#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    string getHint(string secret, string guess) {
        unordered_map<char, int> mp;
        unordered_map<int, int> cnt;
        set<int> st;
        int a = 0, b = 0;
        for (int i = 0; i < secret.size(); ++i) {
            mp[secret[i]] = i;
            ++cnt[secret[i] - '0'];
            if (secret[i] == guess[i]) {
                ++a;
                st.insert(i);
                --cnt[secret[i] - '0'];
            }
        }
        for (int i = 0; i < guess.size(); ++i) {
            if (st.count(i)) {
                continue;
            }
            if (mp.count(guess[i]) && cnt[guess[i] - '0']) {
                if (mp[guess[i]] == i) {
                    ++a;
                } else {
                    ++b;
                }
                --cnt[guess[i] - '0'];
            }
        }
        return to_string(a) + "A" + to_string(b) + "B";
    }
};

/*
"1123"
"0111"
 */

int main() {
    cout << Solution().getHint("11", "10") << std::endl;
    return 0;
}