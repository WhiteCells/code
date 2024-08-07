#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/n-ary-tree-level-order-traversal/
 */

class Node {
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node *> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    vector<vector<int>> levelOrder(Node *root) {
        if (!root) {
            return {};
        }
        vector<vector<int>> res {{root->val}};
        vector<Node *> node_v {root};
        while (!node_v.empty()) {
            vector<Node *> next_node_v;
            vector<int> next_node_val_v;
            for (const auto &node : node_v) {
                for (const auto &node2 : node->children) {
                    next_node_v.push_back(node2);
                    next_node_val_v.push_back(node2->val);
                }
            }
            node_v = std::move(next_node_v);
            if (!next_node_val_v.empty()) {
                res.push_back(next_node_val_v);
            }
        }
        return res;
    }
};

int main() {

    return 0;
}