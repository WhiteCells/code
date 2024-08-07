#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/binary-tree-level-order-traversal-ii/description/
 */

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if (!root) {
            return {};
        }
        vector<vector<int>> res {{root->val}};
        vector<TreeNode *> node_v {root};
        while (!node_v.empty()) {
            vector<TreeNode *> next_node_v;
            vector<int> node_val_v;
            for (const auto &node : node_v) {
                if (node->left) {
                    next_node_v.push_back(node->left);
                    node_val_v.push_back(node->left->val);
                }
                if (node->right) {
                    next_node_v.push_back(node->right);
                    node_val_v.push_back(node->right->val);
                }
            }
            node_v = next_node_v;
            if (!node_val_v.empty()) {
                res.push_back(node_val_v);
            }
        }
        for (int i = 0, j = res.size() - 1; i < j; ++i, --j) {
            vector<int> tmp = res[i];
            res[i] = res[j];
            res[j] = tmp;
        }
        return res;
    }
};

int main() {
    
    return 0;
}