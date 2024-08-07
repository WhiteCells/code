#include "D:\distake\Coding\head_file.h"

class Solution {
public:
    bool isOperator(const string& s) {
        return s == "+" || s == "-" || s == "*" || s == "/";
    }
    int strToint(const string& s) {
        int sum = 0;
        int len = s[0] == '-' ? s.size() - 1 : s.size();
        /* bug 在 size() 接口，size() 返回类型 size_t 为 unsigned int 类型 */
        // for (int i = s.size() - 1, j = 1; i > s.size() - len - 1; --i, j *= 10) {
        //     sum += (s[i] - '0') * j;
        // }
        for (int i = (int)s.size() - 1, j = 1; i > (int)s.size() - len - 1; --i, j *= 10) {
            // signed integer overflow: 147483648 + 2000000000 cannot be represented in type 'int'
            sum += (s[i] - '0') * j;
        }
        return len == s.size() ? sum : -sum;
    }
    string intTostr(int num) {
        string res;
        while (num) {
            res.push_back(num % 10 + 48);
            num /= 10;
        }
        reverse(res.begin(), res.end());
        return res;
        // return to_string(num);
    }
    string operationTwoNum(const string& oper, const string& str1, const string& str2) {
        if (oper == "+") {
            return intTostr(strToint(str1) + strToint(str2));
        }
        else if (oper == "-") {
            return intTostr(strToint(str1) - strToint(str2));
        }
        else if (oper == "*") {
            return intTostr(strToint(str1) * strToint(str2));
        }
        else {
            return intTostr(strToint(str1) / strToint(str2));
        }
    }
    int evalRPN(vector<string>& tokens) {
        stack<string> strStack;
        for (auto& s : tokens) {
            if (isOperator(s)) {
                // 弹出右操作数
                string rightStr = strStack.top();
                strStack.pop();
                // 弹出左操作数
                string leftStr = strStack.top();
                strStack.pop();
                // 结果入栈
                strStack.push(operationTwoNum(s, leftStr, rightStr));
            }
            else {
                strStack.push(s);
            }
        }
        return strToint(strStack.top());
    }
};

class Solution2 {
public:
    long long strTolong(const string& s) {
        // long long res = 0;
        // int count = s[0] == '-' ? (int)s.size() - 1 : (int)s.size();
        // for (int i = (int)s.size() - 1, j = 1; i > (int)s.size() - count - 1; --i, j *= 10) {
        //     res += (s[i] - '0') * j;
        // }
        // return res;
        return stoll(s); // string 转化为 long long 
    }
    int evalRPN(vector<string>& tokens) {
        stack<long long> st;
        for (auto& s : tokens) {
            if (s == "+" || s == "-" || s == "*" || s == "/") {
                long long right = st.top();
                st.pop();
                long long left = st.top();
                st.pop();

                if (s == "+") {
                    st.push(left + right);
                }
                if (s == "-") {
                    st.push(left - right);
                }
                if (s == "*") {
                    st.push(left * right);
                }
                if (s == "/") {
                    st.push(left / right);
                }
            }
            else {
                st.push(strTolong(s));
            }
        }
        return st.top();
    }
};

class Solution3 {
public:
    long long strTolonglong(const string& s) {
        long long sum = 0; // 转化结果
        // int count = s[0] == "-" ? (int)s.size() - 1 : (int)s.size();
        int leftMostSub = s[0] == '-' ? 0 : -1;
        for (int i = (int)s.size() - 1, j = 1; i > leftMostSub; --i, j *= 10) {
            sum += (s[i] - '0') * j;
        }
        return leftMostSub ? sum : -sum;
    }
    int evalRPN(vector<string>& tokens) {
        stack<long long> llStack;
        for (auto& s : tokens) {
            if (s == "+" || s == "-" || s == "*" || s == "/") {
                // 先弹出右操作数
                long long right = llStack.top();
                llStack.pop();
                // 在弹出左操作数
                long long left = llStack.top();
                llStack.pop();
                if (s == "+") {
                    llStack.push(left + right);
                }
                if (s == "-") {
                    llStack.push(left - right);
                }
                if (s == "*") {
                    llStack.push(left * right);
                }
                if (s == "/") {
                    llStack.push(left / right);
                }
            }
            else {
                llStack.push(strTolonglong(s));
            }
        }
        return llStack.top();
    }
};

int main() {
    Solution3 s;
    string str = "123";
    // int num = 123;
    // cout << s.strToint(str) << endl;
    // cout << s.strTolong(str) << endl;
    cout << s.strTolonglong(str) << endl;
    // cout << s.intTostr(num) << endl;
    vector<string> v = { "10","6","9","3","+","-11","*","/","*","17","+","5","+" };
    vector<string> v2 = { "-128","-128","*","-128","*","-128","*","-1","*","8","*" };
    cout << s.evalRPN(v2);
    return 0;
}