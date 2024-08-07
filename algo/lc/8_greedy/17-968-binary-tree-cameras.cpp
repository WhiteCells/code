#include "D:/distake/Coding/head_file.h"

/*
 * @Author: WhiteCells
 * @Date: 2023-05-30 22:25:38
 * @Last Modified by: WhiteCells
 * @Last Modified time: 2023-05-30 22:25:38
 * @Description: 968. 监控二叉树
 * https://leetcode.cn/problems/binary-tree-cameras/
 *
*/


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};


class Solution {
private:
    int res = 0; // 摄像头数
    // 后序遍历，从下向上
    int traversal(TreeNode* cur) {
        // 空结点，该结点有覆盖
        if (!cur) {
            return 2;
        }
        int left = traversal(cur->left);
        int right = traversal(cur->right);

        // 左右子结点都有覆盖
        if (left == 2 && right == 2) {
            return 0; // 该结点无覆盖
        }

        // 左右子结点至少有一个无覆盖
        // left == 0 && right == 0 都无覆盖
        // left == 0 && right == 1 左子结点无覆盖
        // left == 0 && right == 2 左子结点无覆盖
        // left == 1 && right == 0 右子结点无覆盖
        // left == 2 && right == 0 右子结点无覆盖
        if (left == 0 || right == 0) {
            ++res;
            return 1; // 该结点需要摄像头
        }

        // 左右子结点至少含有一个摄像头
        if (left == 1 || right == 1) {
            return 2; // 该结点已被覆盖
        }
        return -1;
    }
public:
    int minCameraCover(TreeNode* root) {
        if (traversal(root) == 0) { // 根结点无覆盖需要一个摄像头
            ++res;
        }
        return res;
    }
};


int main() {
    Solution s;
    TreeNode node5 = TreeNode(0);
    TreeNode node4 = TreeNode(0, &node5, nullptr);
    TreeNode node3 = TreeNode(0, &node4, nullptr);
    TreeNode node2 = TreeNode(0, &node3, nullptr);
    TreeNode node1 = TreeNode(0, &node2, nullptr);
    cout << s.minCameraCover(&node1);
    return 0;
}