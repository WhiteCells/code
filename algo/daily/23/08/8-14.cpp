#include <iostream>
#include <functional>

using namespace std;
// https://leetcode.cn/problems/merge-two-binary-trees/description/

struct TreeNode {
    int val;
    TreeNode* left, * right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int val): val(val), left(nullptr), right(nullptr) {}
    TreeNode(int val, TreeNode* left, TreeNode* right): val(val), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (!root1) {
            return root2;
        }
        if (!root2) {
            return root1;
        }
        if (root1 && root2) {
            root1->val += root2->val;
        }
        root1->left = mergeTrees(root1->left, root2->left);
        root1->right = mergeTrees(root1->right, root2->right);
        return root1;
    }
};

int main() {
    Solution s;
    function<void(TreeNode*)> ergodic = [&](TreeNode* root) {
        if (!root) {
            return;
        }
        ergodic(root->left);
        cout << root->val << ' ';
        ergodic(root->right);

    };
    /* root1 */
    TreeNode* node4 = new TreeNode(5);
    TreeNode* node3 = new TreeNode(3, node4, nullptr);
    TreeNode* node2 = new TreeNode(2);
    TreeNode* root1 = new TreeNode(1, node3, node2);

    /* root2 */
    TreeNode* node24 = new TreeNode(4);
    TreeNode* node21 = new TreeNode(1, nullptr, node24);
    TreeNode* node27 = new TreeNode(7);
    TreeNode* node23 = new TreeNode(3, nullptr, node27);
    TreeNode* root2 = new TreeNode(2, node21, node23);

    TreeNode* root = s.mergeTrees(root1, root2);
    ergodic(root);
    return 0;
}