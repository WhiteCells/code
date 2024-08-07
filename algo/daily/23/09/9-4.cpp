#include "../../head_file.h"

/*
problme: 449. 序列化和反序列化二叉搜索树

序列化是将数据结构或对象转换为一系列位的过程，以便它可以存储在文件或内存缓冲区中，或通过网络连接链路传输，以便稍后在同一个或另一个计算机环境中重建。

设计一个算法来序列化和反序列化 二叉搜索树 。 对序列化/反序列化算法的工作方式没有限制。 您只需确保二叉搜索树可以序列化为字符串，并且可以将该字符串反序列化为最初的二叉搜索树。

编码的字符串应尽可能紧凑。

输入：root = [2,1,3]
输出：[2,1,3]

提示：

    树中节点数范围是 [0, 104]
    0 <= Node.val <= 104
    题目数据 保证 输入的树是一棵二叉搜索树。

url: https://leetcode.cn/problems/serialize-and-deserialize-bst/
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* 数据输入保证是二叉搜索树，所以对其中序遍历，得到的是一个有序数列 */
/*
    给定一颗二叉树的先序遍历和中序遍历可以恢复这颗二叉树
    给定一颗二叉树的后序遍历和中序遍历可以恢复这棵二叉树
    由于二叉搜索树的中序遍历是有序的，因此给定一颗二叉树的先序遍历（或后续遍历），相当于有了中序遍历和先序遍历（或后续遍历），因此只要有先序遍历（或后序遍历）就可以恢复二叉搜索树
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode *root) {
        string res;
        vector<int> pre; // 存放先序遍历
        PerErgodic(root, pre);
        if (0 == pre.size()) {
            return res;
        }
        for (int i = 0; i + 1 < pre.size(); ++i) {
            res.append(to_string(pre[i]) + ",");
        }
        res.append(to_string(pre.back()));
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data) {
        if (0 == data.size()) {
            return nullptr;
        }
        vector<string> arr = Split(data, ',');
        stack<int> st;
        for (const auto &str : arr) {
            st.emplace(stoi(str));
        }
        return Construct(INT_MIN, INT_MAX, st);
    }

    /* 先序遍历 */
    void PerErgodic(TreeNode *root, vector<int> &arr) {
        if (!root) {
            return;
        }
        arr.emplace_back(root->val);
        PerErgodic(root->left, arr);
        PerErgodic(root->right, arr);
    }

    /* split string return vector */
    vector<string> Split(const string &str, const char c) {
        int i = 0, j = 0, n = str.size();
        vector<string> res;
        while (i < n) {
            /* 找到开始位置 */
            while (i < n && c == str[i]) {
                ++i;
            }
            j = i;
            /* 找结束位置 */
            while (i < n && c != str[i]) {
                ++i;
            }
            res.emplace_back(str.substr(j, i - j));
        }
        return res;
    }

    /* vector<int> => tree */
    TreeNode *Construct(int lower, int upper, stack<int> &st) {
        if (0 == st.size() || lower > st.top() || upper < st.top()) {
            return nullptr;
        }
        int val = st.top();
        st.pop();
        TreeNode *root = new TreeNode(val);
        root->right = Construct(val, upper, st);
        root->left = Construct(lower, val, st);
        return root;
    }
};

// class Codec2 {
// public:
//     string serialize(TreeNode *root) {
//         string res;
//         if (!root) {
//             // res += "^";
//             return res;
//         }
//         res += serialize(root->left);
//         res += to_string(root->val);
//         res += ",";
//         res += serialize(root->right);
//         return res;
//     }
//     TreeNode* deserialize(string data) {
//     }
// };

void CreateBinaryTree(TreeNode *&root) {
    cout << "输入节点信息:";
    int val = 0;
    cin >> val;
    root = new TreeNode(val);
    char check = 'n';
    cout << "是否创建" << root->val << "的左孩子 (y/n): ";
    cin >> check;
    if ('y' == check) {
        CreateBinaryTree(root->left);
    }
    cout << "是否创建" << root->val << "的右孩子 (y/n): ";
    cin >> check;
    if ('y' == check) {
        CreateBinaryTree(root->right);
    }
}

void DestoryTree(TreeNode *&root) {
    if (!root) {
        return;
    }
    DestoryTree(root->left);
    DestoryTree(root->right);
    delete root;
}

int main() {
    TreeNode *root = nullptr;
    CreateBinaryTree(root);
    string str = Codec().serialize(root);
    cout << Codec().deserialize(str);
    DestoryTree(root);
    return 0;
}