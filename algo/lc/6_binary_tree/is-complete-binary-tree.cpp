#include "D:/distake/Coding/head_file.h"

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right): val(x), left(left), right(right) {}
};


class Solution {
public:
    bool iscbt(TreeNode* root) {
        queue<TreeNode*> que;
        que.push(root);
        bool flag = false;
        while (!que.empty()) {
            int size = que.size();
            for (int i = 0; i < size; ++i) {
                TreeNode* node = que.front();
                que.pop();
                if (!node->left || !node->right) {
                    flag = true;
                    break;
                }
                if (node->left) {
                    que.push(node->left);
                }
                if (node->right) {
                    que.push(node->right);
                }
            }
            if (flag) {
                break;
            }
        }
        return que.empty();
    }
};

int main() {

    TreeNode node6(6);
    TreeNode node5(5);
    TreeNode node4(4);
    TreeNode node3(3, &node6, nullptr);
    TreeNode node2(2, &node4, &node5);
    TreeNode node1(1, &node2, &node3);
    Solution s;
    cout << s.iscbt(&node1);
    return 0;
}