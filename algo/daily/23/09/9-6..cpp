#include "../../head_file.h"

/*
problme: 1123. 最深叶节点的最近公共祖先
给你一个有根节点 root 的二叉树，返回它 最深的叶节点的最近公共祖先 。

回想一下：

    叶节点 是二叉树中没有子节点的节点
    树的根节点的 深度 为 0，如果某一节点的深度为 d，那它的子节点的深度就是 d+1
    如果我们假定 A 是一组节点 S 的 最近公共祖先，S 中的每个节点都在以 A 为根节点的子树中，且 A 的深度达到此条件下可能的最大值。

输入：root = [3,5,1,6,2,0,8,null,null,7,4]
输出：[2,7,4]
解释：我们返回值为 2 的节点，在图中用黄色标记。
在图中用蓝色标记的是树的最深的节点。
注意，节点 6、0 和 8 也是叶节点，但是它们的深度是 2 ，而节点 7 和 4 的深度是 3 。
提示：

    树中的节点数将在 [1, 1000] 的范围内。
    0 <= Node.val <= 1000
    每个节点的值都是 独一无二 的。

url: https://leetcode.cn/problems/lowest-common-ancestor-of-deepest-leaves/
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
private:
    int DFS(TreeNode *root) {
        if (!root) {
            return 0;
        }
        return max(DFS(root->left), DFS(root->right)) + 1;
    }
public:
    TreeNode *lcaDeepestLeaves(TreeNode *root) {
        int left_depth = DFS(root->left), right_depth = DFS(root->right);
        if (left_depth == right_depth) {
            return root;
        }
        else if (left_depth < right_depth) {
            return lcaDeepestLeaves(root->right);
        }
        return lcaDeepestLeaves(root->left);
    }
};

int main() {
    Solution s;

    return 0;
}