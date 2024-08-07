#include "../../head_file.h"

/*
problme:

url:
 */

class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
    TreeNode(int val, TreeNode *left, TreeNode *right) : val(val), left(left), right(right) {}
};

// vector<int> build tree
// -1 = nullptr
// 8,8,null,7,7,null,null,2,4,null,8,null,7,null,1
class BuildTree {
public:
    BuildTree(vector<int> &v) : index(0), v(v) {}
    TreeNode *buildTree() {

    }
private:
    int index;
    vector<int> v;
};

class Solution {
public:
    int pseudoPalindromicPaths(TreeNode *root) {
        int res = 0;
        int mp[10] {};
        function<void(TreeNode *)> dfs = [&](TreeNode *node) -> void {
            ++mp[node->val];
            if (!node->left && !node->right) {
                int cnt = 0;
                for (int i = 0; i < 10; ++i) {
                    cnt += (mp[i] & 1);
                }
                res += (cnt <= 1);
                return;
            }
            if (node->left) {
                dfs(node->left);
                --mp[node->left->val];
            }
            if (node->right) {
                dfs(node->right);
                --mp[node->right->val];
            }
        };
        dfs(root);
        return res;
    }
};

int main() {
    TreeNode *root5 = new TreeNode(3);
    TreeNode *root4 = new TreeNode(1);
    TreeNode *root3 = new TreeNode(1);
    TreeNode *root2 = new TreeNode(1, nullptr, root3);
    TreeNode *root1 = new TreeNode(3, root5, root4);
    TreeNode *root = new TreeNode(2, root1, root2);

    cout << Solution().pseudoPalindromicPaths(root) << '\n';
    return 0;
}