#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() :val(0), left(nullptr), right(nullptr) {}
    TreeNode(int val) :val(val), left(nullptr), right(nullptr) {}
    TreeNode(int val, TreeNode* left, TreeNode* right) :val(val), left(left), right(right) {}
};

// 给定一个有 N 个结点的二叉树的根结点 root，树中的每个结点上都对应有 node.val 枚硬币，并且总共有 N 枚硬币。
// 在一次移动中，我们可以选择两个相邻的结点，然后将一枚硬币从其中一个结点移动到另一个结点。(移动可以是从父结点到子结点，或者从子结点移动到父结点。)。
// 返回使每个结点上只有一枚硬币所需的移动次数。

class Solution {
private:
    int cnt = 0;
    int ergodic(TreeNode* root) {
        if (!root) {
            return 0;
        }
        if (root->left) {
            root->val += ergodic(root->left);
        }
        if (root->right) {
            root->val += ergodic(root->right);
        }
        cnt += abs(root->val - 1);
        return root->val - 1;
    }
public:
    int distributeCoins(TreeNode* root) {
        ergodic(root);
        return cnt;
    }
};

int main() {
    TreeNode node2(0);
    TreeNode node3(0);
    TreeNode node1(3, &node2, &node3);
    Solution s;
    cout << s.distributeCoins(&node1);
    return 0;
}