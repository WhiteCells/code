#include "../../head_file.h"

/*
problme:

url:
 */

class TreeNode {
public:
    TreeNode() : left(nullptr), right(nullptr), val(0) {}
    TreeNode(int val) : left(nullptr), right(nullptr), val(val) {}
    TreeNode(int val, TreeNode *left, TreeNode *right) : left(left), right(right), val(val) {}
    TreeNode *left;
    TreeNode *right;
    int val;
};

class Solution {
public:
    TreeNode *constructFromPrePost(vector<int> &preorder, vector<int> &postorder) {
        int n = preorder.size();
        unordered_map<int, int> mp;
        for (int i = 0; i < n; ++i) {
            mp[postorder[i]] = i;
        }
        function<TreeNode *(int, int, int, int)> dfs = [&](int pre_left, int pre_right, int post_left, int post_right) -> TreeNode * {
            if (pre_left > pre_right) {
                return nullptr;
            }
            int left_cnt = 0;
            if (pre_left < pre_right) {
                left_cnt = mp[preorder[pre_left + 1]] - post_left + 1;
            }
            return new TreeNode(preorder[pre_left],
                                dfs(pre_left + 1, pre_left + left_cnt, post_left, post_left + left_cnt - 1),
                                dfs(pre_left + left_cnt + 1, pre_right, post_left + left_cnt, post_right - 1));
        };
        return dfs(0, n - 1, 0, n - 1);
    }
};

int main() {

    return 0;
}