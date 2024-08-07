#include <iostream>
#include <string>
#include <vector>

using namespace std;
// https://leetcode.cn/problems/remove-comments/

// /*Test program */
// int main()
// { 
//   // variable declaration 
// int a, b, c;
// /* This is a test
//    multiline  
//    comment for 
//    testing */
// a = b + c;
// }

class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        bool flag = false; // 多行注释 判断是否跳过下一行
        vector<string> res;
        string s;
        for (const auto& line : source) {
            int len = line.size();
            for (int i = 0; i < len; ++i) {
                // 单行注释
                if (!flag && i < len - 1 && '/' == line[i] && '/' == line[i + 1]) {
                    break;
                }
                // 多行注释开始
                if (!flag && i < len - 1 && '/' == line[i] && '*' == line[i + 1]) {
                    flag = true;
                    ++i; // for 继续再次 ++i，不能 i += 2
                    continue;
                }
                // 多行注释结束
                if (flag && i < len - 1 && '*' == line[i] && '/' == line[i + 1]) {
                    flag = false;
                    ++i;
                    continue;
                }
                // 多行注释 跨行 中的行跳过
                if (flag) {
                    continue;
                }
                s += line[i];
            }
            // s 非空且多行注释结束
            if (!s.empty() && !flag) {
                res.push_back(s);
                s.clear();
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    // auto source = vector<string>{
    //     "/*Test program */",
    //     "int main()",
    //     "{ ",
    //     "  // variable declaration ",
    //     "int a, b, c;",
    //     "/* This is a test",
    //     "   multiline  ",
    //     "   comment for ",
    //     "   testing */",
    //     "a = b + c;",
    //     "}"
    // };
    auto source = vector<string>{
        "a/*comment",
        "line",
        "more_comment*/b"
    };
    auto res = s.removeComments(source);
    for (auto& ele : res) {
        cout << ele << '\n';
    }
    return 0;
}