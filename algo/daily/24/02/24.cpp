#include "../../head_file.h"

/*
problme:

url:https://leetcode.cn/problems/closest-nodes-queries-in-a-binary-search-tree/
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
    vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries) {
        midOrder(root);
        vector<vector<int>> res;

        for (const auto &q : queries) {

            int left = 0, right = node_val_v.size() - 1;

            while (left <= right) {
                int mid = ((right - left) >> 1) + left;

                if (node_val_v[mid] == q) {
                    res.push_back({node_val_v[mid], node_val_v[mid]});
                    break;
                } else if (node_val_v[mid] < q) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }

                if (left > right) {
                    if (left == node_val_v.size()) {
                        res.push_back({node_val_v[right], -1});
                    } else if (right == -1) {
                        res.push_back({-1, node_val_v[left]});
                    } else {
                        res.push_back({node_val_v[right], node_val_v[left]});
                    }
                }
            }
        }

        return res;
    }
    
    vector<int> node_val_v;

    void midOrder(TreeNode *root) {
        if (!root) {
            return;
        }
        
        midOrder(root->left);
        node_val_v.push_back(root->val);
        midOrder(root->right);
    }
};

int main() {

    return 0;
}