#include <iostream>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
};

void CreateTree(TreeNode *&root) {
    char check;
    root = new TreeNode;
    cout << "输入节点信息:" << '\n';
    cin >> root->val;
    cout << "是否添加" << root->val << "的左孩子? (y/n):" << '\n';
    cin >> check;
    if ('y' == check) {
        CreateTree(root->left);
    }
    else {
        root->left = nullptr;
    }
    cout << "是否添加" << root->val << "的右孩子? ((y/n):" << '\n';
    cin >> check;
    if ('y' == check) {
        CreateTree(root->right);
    }
    else {
        root->right = nullptr;
    }
}

void CreateTree2(TreeNode *&root) {
    char ch;
    cin >> ch;
    if ('#' != ch) {
        root = new TreeNode;
        root->val = ch;
        CreateTree2(root->left);
        CreateTree2(root->right);
    }
    else {
        root = nullptr;
    }
}

void PreOrder(TreeNode *root) {
    if (root) {
        stack<TreeNode *> s;
        s.push(root);
        while (!s.empty()) {
            root = s.top();
            cout << root->val << ' ';
            s.pop();
            if (root->right) {
                s.push((root->right));
            }
            if (root->left) {
                s.push(root->left);
            }
        }
    }
}

void PreorderTraversal(TreeNode *root) {
    if (!root) {
        return;
    }
    cout << root->val << ' ';
    PreorderTraversal(root->left);
    PreorderTraversal(root->right);
}

void MiddleOrderTraversal(TreeNode *root) {
    if (!root) {
        return;
    }
    MiddleOrderTraversal(root->left);
    cout << root->val << ' ';
    MiddleOrderTraversal(root->right);
}

void SequentialTraversal(TreeNode *root) {
    if (!root) {
        return;
    }
    SequentialTraversal(root->left);
    SequentialTraversal(root->right);
    cout << root->val << ' ';
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
    CreateTree(root);
    PreOrder(root);
    // CreateTree2(root);
    // PreorderTraversal(root);
    // cout << '\n';
    // MiddleOrderTraversal(root);
    // cout << '\n';
    // SequentialTraversal(root);
    // cout << '\n';
    DestoryTree(root);
    return 0;
}