#include "../head_file.h"
/*
 * @lc app=leetcode.cn id=100 lang=cpp
 *
 * [100] 相同的树
 *
 * https://leetcode.cn/problems/same-tree/description/
 *
 * algorithms
 * Easy (60.51%)
 * Likes:    1103
 * Dislikes: 0
 * Total Accepted:    514.5K
 * Total Submissions: 850.1K
 * Testcase Example:  '[1,2,3]\n[1,2,3]'
 *
 * 给你两棵二叉树的根节点 p 和 q ，编写一个函数来检验这两棵树是否相同。
 * 
 * 如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：p = [1,2,3], q = [1,2,3]
 * 输出：true
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：p = [1,2], q = [1,null,2]
 * 输出：false
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：p = [1,2,1], q = [1,1,2]
 * 输出：false
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 两棵树上的节点数目都在范围 [0, 100] 内
 * -10^4 
 * 
 * 
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// @lc code=start
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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        function<bool(TreeNode *, TreeNode *)> dfs = [&](TreeNode *root1, TreeNode *root2) -> bool {
            if (!root1 && !root2) {
                return true;
            } else if (!root1 || !root2) {
                return false;
            } else if (root1->val == root2->val) {
                return dfs(root1->left, root2->left) && dfs(root1->right, root2->right);
            } else if (root1->val != root2->val){
                return false;
            }
            return false;
        };
        return dfs(p, q);
    }
};
// @lc code=end


int main() {
    Solution s;
    TreeNode *root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(1);

    TreeNode *root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(1);

    cout << s.isSameTree(root1, root2) << endl;
    return 0;
}