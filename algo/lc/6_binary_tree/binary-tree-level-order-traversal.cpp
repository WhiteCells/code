#include "D:\distake\Coding\head_file.h"

// 广度优先搜索

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right): val(x), left(left), right(right) {}
};

/* BUG */
// class Solution {
// public:
//     vector<vector<int>> levelOrder(TreeNode* root) {
//         if (!root) {
//             return {};
//         }
//         vector<vector<int>> rev; // 返回结果容器
//         vector<TreeNode*> nodev; // 结点容器

//         nodev.emplace_back(root); // 根结点放进结点容器
//         rev.push_back({ root->val }); // 根结点数据域压入容器

//         while (!nodev.empty()) {
//             vector<TreeNode*> tmpnodev;
//             vector<int> v; // 每一层结果容器
//             for (auto& node : nodev) {
//                 // 左结点非空，左结点和值分别压入容器
//                 if (node->left) {
//                     tmpnodev.push_back(node->left);
//                     v.push_back(node->left->val);
//                 }
//                 // 右结点非空，左结点和值分别压入容器
//                 if (node->right) {
//                     tmpnodev.push_back(node->right);
//                     v.push_back(node->right->val);
//                 }
//                 // 每一层结果非空，压入容器
//                 if (!v.empty()) {
//                     rev.push_back(v);
//                 }
//             }
//             // 更新结点容器
//             nodev = tmpnodev;
//         }
//         return rev;
//     }
// };

// 数组方法
class Solution1 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) {
            return {};
        }
        vector<vector<int>> rev; // 返回结果容器
        vector<TreeNode*> nodev; // 当前层结点容器

        nodev.push_back(root); // 根结点放进结点容器

        while (!nodev.empty()) {
            vector<TreeNode*> next; // 下一层的结点容器
            vector<int> vals; // 当前层结果容器
            for (auto& node : nodev) {
                // 结点的值放入 vals
                vals.push_back(node->val);
                // 结点孩子非空，放入下一层结点容器
                if (node->left) {
                    next.push_back(node->left);
                }
                if (node->right) {
                    next.push_back(node->right);
                }
            }
            // 更新当前层结点容器
            nodev = next;
            // 每一层结果 vals 压入 返回结果容器 rev
            rev.push_back(vals);
        }
        return rev;
    }
};

// 队列方法
class Solution2 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) {
            return {};
        }

        queue<TreeNode*> que;
        que.push(root);
        vector<vector<int>> rev;

        while (!que.empty()) {
            int size = que.size();
            vector<int> vals;
            for (int i = 0; i < size; ++i) {
                // 取出队头
                TreeNode* node = que.front();
                que.pop();
                vals.push_back(node->val);
                // 头结点的左右孩子
                if (node->left) {
                    que.push(node->left);
                }
                if (node->right) {
                    que.push(node->right);
                }
            }
            rev.push_back(vals);
        }
        return rev;
    }
};

// 递归方法
class Solution3 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        pre(root, 0);
        return rev;
    }
    void pre(TreeNode* root, int depth) {
        if (!root) return;
        if (depth >= rev.size()) {
            rev.push_back(vector<int> {});
        }
        rev[depth].push_back(root->val);

        pre(root->left, depth + 1);
        pre(root->right, depth + 1);
    }
    vector<vector<int>> rev;
};


int main() {
    TreeNode node1_1(4);
    TreeNode node1_2(5);

    TreeNode node1(2, &node1_1, &node1_2);
    TreeNode node2(3);

    TreeNode root(1, &node1, &node2);

    // Solution1 s;
    Solution2 s;
    // Solution3 s;
    vector<vector<int>> rev = s.levelOrder(&root);

    for (auto& v : rev) {
        for (auto& x : v) {
            cout << x << " ";
        }
    }
    return 0;
}