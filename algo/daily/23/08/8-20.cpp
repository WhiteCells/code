#include "../../head_file.h"

/*
problme: 2236. 判断根结点是否等于子结点之和
给你一个 二叉树 的根结点 root，该二叉树由恰好 3 个结点组成：根结点、左子结点和右子结点。
如果根结点值等于两个子结点值之和，返回 true ，否则返回 false 。
url: https://leetcode.cn/problems/root-equals-sum-of-children/description/
输入：root = [10,4,6]
输出：true
解释：根结点、左子结点和右子结点的值分别是 10 、4 和 6 。
由于 10 等于 4 + 6 ，因此返回 true 。
提示：
    树只包含根结点、左子结点和右子结点
    -100 <= Node.val <= 100
@Author: Eorys
@Date: 2023-08-20 06:48:25
@Last Modified by: Eorys
@Last Modified time: 2023-08-20 06:48:25
@Description:
*/

struct TreeNode {
    int val;
    TreeNode* left, *right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int val): val(val), left(nullptr), right(nullptr) {}
    TreeNode(int val, TreeNode* left, TreeNode* right): val(val), left(left), right(right) {}
};

class Solution {
public:
    bool checkTree(TreeNode* root) {
        return root->val == root->left->val + root->right->val;
    }
};

int main() {
    Solution s;

    return 0;
}