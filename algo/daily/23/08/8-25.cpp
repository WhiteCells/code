#include "../../head_file.h"

/*
problme: 1448. 统计二叉树中好节点的数目
给你一棵根为 root 的二叉树，请你返回二叉树中好节点的数目。
「好节点」X 定义为：从根到该节点 X 所经过的节点中，没有任何节点的值大于 X 的值。
输入：root = [3,1,4,3,null,1,5]
输出：4
解释：图中蓝色节点为好节点。
根节点 (3) 永远是个好节点。
节点 4 -> (3,4) 是路径中的最大值。
节点 5 -> (3,4,5) 是路径中的最大值。
节点 3 -> (3,1,3) 是路径中的最大值。
提示：
    二叉树中节点数目范围是 [1, 10^5] 。
    每个节点权值的范围是 [-10^4, 10^4] 。
url: https://leetcode.cn/problems/count-good-nodes-in-binary-tree/
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
    int res = 0;
    int recursion(TreeNode* root, int val) {
        if (!root) {
            return res;
        }
        if (root->val >= val) {
            ++res;
            val = root->val;
        }
        return recursion(root->left, val) + recursion(root->right, val);
    }
    int goodNodes(TreeNode* root) {
        recursion(root, root->val);
        return res;
    }
};


int main() {
    Solution s;

    return 0;
}