#include "../../head_file.h"

/*
problme: 

url: https://leetcode.cn/problems/cousins-in-binary-tree/
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        vector<TreeNode *> node_v {root};
        while (!node_v.empty()) {
            vector<TreeNode *> next_node_v;
            int cnt = 0;
            for (const auto &node : node_v) {
                if (node->left) {
                    next_node_v.push_back(node->left);
                    if (node->left->val == x || node->left->val == y) {
                        ++cnt;
                    }
                }
                if (node->right) {
                    next_node_v.push_back(node->right);
                    if (node->right->val == x || node->right->val == y) {
                        ++cnt;
                    }
                }
                if (node->left && node->right) {
                    if ((node->left->val == x && node->right->val == y)
                    || (node->left->val == y && node->right->val == x)) {
                        return false;
                    }
                }
            }
            if (cnt == 1) {
                return false;
            }
            node_v = next_node_v;
        }
        return true;
    }
};

int main() {
    
    return 0;
}