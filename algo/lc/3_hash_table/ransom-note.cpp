#include "D:\distake\Coding\head_file.h"

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> unmap;
        for (auto& c : ransomNote) {
            unmap[c]++;
        }
        for (auto& c : magazine) {
            if (unmap.find(unmap[c]) != unmap.end()) {
                unmap[c]--;
                if (unmap[c] < 0) {
                    return false;
                }
            }
        }
        return true;
    }
    bool canConstruct2(string ransomNote, string magzine) {
        if (ransomNote.size() > magzine.size()) return false;

        int arr[26] = { 0 };
        for (int i = 0; i < ransomNote.size(); ++i) {
            arr[ransomNote[i] - 'a']++;
        }
        for (int i = 0; i < magzine.size(); ++i) {
            arr[magzine[i] - 'a']--;
            if (arr[magzine[i] - 'a'] < 0) {
                return false;
            }
        }
        return true;
    }
    bool canConstruct3(string ransomNote, string magzine) {
        if (ransomNote.size() > magzine.size()) return false;

        vector<int> v(26, 0);
        for (int i = 0; i < ransomNote.size(); ++i) {
            v[ransomNote[i] - 'a']++;
        }
        for (int i = 0; i < magzine.size(); ++i) {
            v[magzine[i] - 'a']--;
            if (v[magzine[i] - 'a'] < 0) {
                return false;
            }
        }
        return true;
    }
    bool canConstruct4(string ransomNote, string magazine) {
        if (ransomNote.size() > magazine.size()) return false;

        vector<int> v(26, 0);
        // 对报纸出现的字符进行统计，字符作为 key，出现次数作为 value
        for (auto& c : magazine) {
            v[c - 'a']++;
        }
        // 在报纸的表中去查找赎金信中出现的字符
        for (auto& c : ransomNote) {
            v[c - 'a']--;
            // 赎金信中出现的相同的字符的次数比报纸中多，就说明不对应
            if (v[c - 'a'] < 0) return false;
        }
        return true;
    }
    bool canConstruct5(string ransomNote, string magazine) {
        if (ransomNote.size() > magazine.size()) return false;
        int arr[26] = { 0 };
        for (int i = 0; i < magazine.size(); ++i) {
            arr[magazine[i] - 'a']++;
        }
        for (int i = 0; i < ransomNote.size(); ++i) {
            arr[ransomNote[i] - 'a']--;
            if (arr[ransomNote[i] - 'a'] < 0) return false;
        }
        return true;
    }
    bool canConstruct6(string ransomNote, string magazine) {
        if (ransomNote.size() > magazine.size()) return false;
        unordered_map<char, int> unmap;
        for (auto& c : magazine) {
            unmap[c]++;
        }
        for (auto& c : ransomNote) {
            unmap[c]--;
            if (unmap[c] < 0) return false;
        }
        return true;
    }
};

int main() {
    string s1 = "aa";
    string s2 = "aab";
    Solution s;
    cout << s.canConstruct6(s1, s2);
    return 0;
}