#include "D:/distake/Coding/head_file.h"


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right): val(x), left(left), right(right) {}
};

// class Solution {
// public:
//     vector<int> preorderTraversal(TreeNode* root) {
//         if (root == nullptr) {
//             return rev;
//         }
//         rev.push_back(root->val);
//         preorderTraversal(root->left);
//         preorderTraversal(root->right);
//         return rev;
//     }
//     vector<int> rev;
// };

// 先序遍历
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        if (!root) {
            return {};
        }
        vector<int> rev;
        stack<TreeNode*> st;
        TreeNode* node = root;
        // st.push(node);
        st.emplace(node);
        while (!st.empty()) {
            node = st.top();
            st.pop();
            // rev.push_back(node->val);
            rev.emplace_back(node->val);
            if (node->right) {
                st.push(node->right);
            }
            if (node->left) {
                st.push(node->left);
            }
        }
        return rev;
    }
};

