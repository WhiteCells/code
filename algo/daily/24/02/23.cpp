#include "../../head_file.h"

/*
problme:

url:
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
    long long kthLargestLevelSum(TreeNode *root, int k) {
        vector<TreeNode *> node_v {root};
        priority_queue<long long> sum_q;

        while (!node_v.empty()) {
            vector<TreeNode *> next_node;
            long long sum = 0;

            for (const auto &node : node_v) {
                sum += node->val;
                if (node->left) {
                    next_node.push_back(node->left);
                }
                if (node->right) {
                    // next_node.emplace_back(node->right);
                    next_node.push_back(node->right);
                }
            }

            node_v = std::move(next_node);
            sum_q.push(sum);
        }

        if (k > sum_q.size()) {
            return -1;
        }

        while (--k) {
            sum_q.top();
        }

        return sum_q.top();
    }
};

int main() {

    return 0;
}