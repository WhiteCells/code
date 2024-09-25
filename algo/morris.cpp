#include <iostream>

class TreeNode
{
public:
    TreeNode() :
        val(0), left(nullptr), right(nullptr) {}

    TreeNode(int val) :
        val(val), left(nullptr), right(nullptr) {}

    TreeNode(int val, TreeNode *left, TreeNode *right) :
        val(val), left(left), right(right) {}

    void test() {}

    TreeNode *left, *right;
    int val;
};

void morrisMid2(TreeNode *root)
{
    while (root) {
        if (!root->right) {
            // 右子节点为空
            // 处理当前节点
            // 遍历当前节点的左子节点
            std::cout << root->val << std::endl;
            root = root->left;
        }
        else {
            // 右子节点非空
            TreeNode *pre = root->right;
            while (pre->left && pre->left != root) {
                // 找到当前节点右子树的最左节点，前驱节点
                pre = pre->left;
            }
            if (!pre->left) {
                // 如果最左节点的左指针为空
                // 最左节点的左指针指向当前节点
                // 遍历当前节点的右子节点
                pre->left = root;
                root = root->right;
            }
            else {
                // 如果最左节点的左指针非空
                // 将最左节点的左指针置为空
                // 处理当前节点
                // 当前节点置为其左节点
                pre->left = nullptr;
                std::cout << root->val << std::endl;
                root = root->left;
            }
        }
    }
}

void morrisMid(TreeNode *root)
{
    TreeNode *cur = root;
    while (cur) {
        // 当前节点左节点为空
        if (!cur->left) {
            // 处理当前节点
            std::cout << cur->val << std::endl;
            // 遍历当前节点右节点
            cur = cur->right;
        }
        else {
            // 当前节点左节点非空
            // 找到当前节点左子树的最右节点，前驱节点
            TreeNode *pre = cur->left;
            while (pre->right && pre->right != cur) {
                // 遍历到右节点
                pre = pre->right;
            }
            // 前驱节点的右指针指向了当前节点
            // 说明第一次访问该前驱节点
            if (pre->right != cur) {
                // 前驱节点的右指针指向当前节点
                pre->right = cur;
                // 遍历当前节点左子树
                cur = cur->left;
            }
            else {
                // 前驱节点右节点被设置
                // 前驱节点置为空，还原二叉树
                pre->right = nullptr;
                // 处理当前节点
                std::cout << cur->val << std::endl;
                // 遍历当前节点右子树
                cur = cur->right;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    TreeNode node1(4);
    TreeNode node2(5);
    TreeNode node3(3, &node1, &node2);
    TreeNode node4(2);
    TreeNode node5(1, &node4, &node3);
    //     1
    //    / \
    //   2   3
    //      / \
    //     4   5
    // morrisMid2(&node5);
    // std::cout << node1.val << std::endl;
    // std::cout << node2.val << std::endl;
    // std::cout << node3.val << std::endl;
    // std::cout << node4.val << std::endl;
    // std::cout << node5.val << std::endl;
    morrisMid(&node5);
    return 0;
}
