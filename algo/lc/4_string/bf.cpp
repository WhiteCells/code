#include "D:\distake\Coding\head_file.h"

int BruteForce(const string& s1, const string& s2) {
    int i = 0, j = 0;
    for (; i < s1.size(); ++i) {
        if (s1[i] == s2[j]) {
            if (j == s2.size() - 1) {
                break;
            }
            j++;
        }
        else {
            j = 0;
        }
    }
    return i - j;
}

int main() {
    string s1 = "abcbacbc";
    string s2 = "ba";
    cout << BruteForce(s1, s2);
    return 0;
}