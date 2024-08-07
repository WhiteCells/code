#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int numJewelsInStones(string jewels, string stones) {
        int mp[52]{ 0 };
        for (const auto& j : jewels) {
            // 大写字母
            if (j >= 65 && j <= 90) {
                mp[j - 'A'] = 1;
            }
            // 小写字母
            else {
                mp[j - 'A' - 6] = 1;
            }
        }
        int ans = 0;
        for (const auto& s : stones) {
            if (s >= 65 && s <= 90 && mp[s - 'A']
                || s >= 97 && s <= 122 && mp[s - 'A' - 6]) {
                ++ans;
            }
        }
        return ans;
    }
};


int main() {
    Solution s;
    cout << s.numJewelsInStones("aA", "aAAbbbb");
    // 65 90 97 122 
    printf("%d ", 'A');
    printf("%d ", 'Z');
    printf("%d ", 'a');
    printf("%d ", 'z');
    return 0;
}


