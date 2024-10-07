#include <iostream>
#include <vector>
#include <string>

// 计算部分匹配表（next 数组）
std::vector<int> computeNextArray(const std::string &pattern)
{
    int m = pattern.size();
    std::vector<int> next(m, 0);
    int j = 0; // 记录当前匹配的前缀长度

    for (int i = 1; i < m; i++) {
        // 不匹配时，回退到前一个匹配的位置
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1];
        }

        // 如果字符匹配，当前匹配长度加一
        if (pattern[i] == pattern[j]) {
            j++;
        }

        next[i] = j; // 记录前缀匹配的长度
    }
    return next;
}

// KMP 字符串匹配
// 返回所有匹配的位置
std::vector<int> KMP(const std::string &text, const std::string &pattern)
{
    std::vector<int> next = computeNextArray(pattern);
    std::vector<int> result;
    int n = text.size();
    int m = pattern.size();
    int j = 0; // 模式串的匹配索引

    for (int i = 0; i < n; i++) {
        // 如果当前字符不匹配，使用 next 数组找到新的匹配位置
        while (j > 0 && text[i] != pattern[j]) {
            j = next[j - 1];
        }

        // 如果字符匹配，模式串索引加一
        if (text[i] == pattern[j]) {
            j++;
        }

        // 如果匹配到了整个模式串，记录匹配位置
        if (j == m) {
            result.push_back(i - m + 1);
            j = next[j - 1]; // 继续寻找下一个匹配
        }
    }

    return result;
}

int main()
{
    std::string text = "ABABDABACDABABCABAB";
    std::string pattern = "ABABCABAB";

    std::vector<int> matches = KMP(text, pattern);

    std::cout << "Pattern found at indices: ";
    for (int index : matches) {
        std::cout << index << " ";
    }
    std::cout << std::endl;

    return 0;
}