#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/cousins-in-binary-tree-ii/
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode *replaceValueInTree(TreeNode *root) {
        vector<TreeNode *> node_v {root};
        root->val = 0;
        while (!node_v.empty()) {
            vector<TreeNode *> next_node_v;
            int sum = 0;
            for (const auto &node : node_v) {
                if (node->left) {
                    next_node_v.push_back(node->left);
                    sum += node->left->val;
                }
                if (node->right) {
                    next_node_v.push_back(node->right);
                    sum += node->right->val;
                }
            }
            for (const auto &node : node_v) {
                int child_sum = (node->left ? node->left->val : 0) + (node->right ? node->right->val : 0);
                if (node->left) {
                    node->left->val = sum - child_sum;
                }
                if (node->right) {
                    node->right->val = sum - child_sum;
                }
            }
            node_v = next_node_v;
        }
        return root;
    }
};

int main() {

    return 0;
}