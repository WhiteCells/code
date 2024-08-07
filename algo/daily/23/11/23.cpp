#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    /*
    双引号：字符实体为 &quot; ，对应的字符是 " 。
    单引号：字符实体为 &apos; ，对应的字符是 ' 。
    与符号：字符实体为 &amp; ，对应对的字符是 & 。
    大于号：字符实体为 &gt; ，对应的字符是 > 。
    小于号：字符实体为 &lt; ，对应的字符是 < 。
    斜线号：字符实体为 &frasl; ，对应的字符是 / 。
     */
    string entityParser(string text) {
        unordered_map<string, char> mp {
            {"&quot;", '"'},
            {"&apos;", '\''},
            {"&amp;", '&'},
            {"&gt;", '>'},
            {"&lt;", '<'},
            {"&frasl;", '/'},
        };
        for (int i = 0; i < text.size(); ++i) {
            if ('&' == text[i]) {
                int j = i;
                while (j < text.size() && ';' != text[j++]) {}
                string sub = text.substr(i, j - i);
                int sz = sub.size();
                if (mp.count(sub)) {
                    text.erase(text.begin() + i, text.begin() + j);
                    text.insert(text.begin() + i, mp[sub]);
                }
            }
        }
        return text;
    }
};


class Solution1 {
public:
    /*
    双引号：字符实体为 &quot; ，对应的字符是 " 。
    单引号：字符实体为 &apos; ，对应的字符是 ' 。
    与符号：字符实体为 &amp; ，对应对的字符是 & 。
    大于号：字符实体为 &gt; ，对应的字符是 > 。
    小于号：字符实体为 &lt; ，对应的字符是 < 。
    斜线号：字符实体为 &frasl; ，对应的字符是 / 。
     */
    string entityParser(string text) {
        unordered_map<string, char> mp {
            {"&quot;", '"'},
            {"&apos;", '\''},
            {"&amp;", '&'},
            {"&gt;", '>'},
            {"&lt;", '<'},
            {"&frasl;", '/'},
        };
        string res;
        for (int i = 0; i < text.size(); ++i) {
            bool flag = false;
            char c;
            int cnt = 0;
            if ('&' == text[i]) {
                int j = i;
                while (j < text.size() && ';' != text[j++]) {}
                string sub = text.substr(i, j - i);
                if (mp.count(sub)) {
                    flag = true;
                    c = mp[sub];
                    cnt = j - i - 1;
                }
            }
            if (flag) {
                res += c;
                i += cnt;
            } else {
                res += text[i];
            }
        }
        return res;
    }
};

int main() {
    string text = "&amp; is an HTML entity but &ambassador; is not.";
    cout << Solution1().entityParser(text) << endl;
    return 0;
}