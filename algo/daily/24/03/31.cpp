#include "../../head_file.h"

/*
problme:

url:
 */

class Solution {
public:
    bool isValidSerialization(string preorder) {
        stack<int> st;
        st.push(1);
        // 空节点，st.top() - 1
        // 非空节点，st.top() - 1, st.push(2)
        // when st.top() == 0, st.pop()
        int n = preorder.size(), i = 0;
        while (i < n) {
            if (st.empty()) {
                return false;
            }
            if (preorder[i] == '#') {
                st.top() -= 1;
                if (st.top() == 0) {
                    st.pop();
                }
            } else if (preorder[i] != '#' && preorder[i] != ',') {
                // 注意数字的位数
                while (i < n && preorder[i] != ',') {
                    ++i;
                }
                st.top() -= 1;
                if (st.top() == 0) {
                    st.pop();
                }
                st.push(2);
            }
            ++i;
        }
        return st.empty();
    }
};

int main() {
    string preorder {"9,#,92,#,#"};
    cout << Solution().isValidSerialization(preorder) << std::endl;
    return 0;
}