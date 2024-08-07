#include "D:/distake/Coding/head_file.h"

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

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right): val(x), left(left), right(right) {}
};

// 层序遍历
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode*> que;
        que.push(root);
        bool flag = false;
        while (!que.empty()) {
            int size = que.size();
            int count = 0;
            queue<TreeNode*> tmpque = que;
            for (int i = 0; i < size; ++i) {
                TreeNode* node = que.front();
                que.pop();
                if (node->left) {
                    que.push(node->left);
                }
                if (node->right) {
                    que.push(node->right);
                }
            }
            if (que.empty()) {
                que = tmpque;
                break;
            }
        }
        return que.front()->val;
    }
};

int main() {
    TreeNode node3(3);
    TreeNode node2(1);
    TreeNode node1(2, &node2, &node3);
    Solution s;
    cout << s.findBottomLeftValue(&node1);
    return 0;
}