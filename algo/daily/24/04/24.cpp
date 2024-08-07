#include "../../head_file.h"

/*
problme:

url:
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val, TreeNode *left, TreeNode *right)
        : val(val), left(left), right(right) {}
};

class Solution {
public:
    int amountOfTime(TreeNode *root, int start) {
        unordered_map<int, vector<int>> graph;
        function<void(TreeNode *)> dfs = [&](TreeNode *node) {
            for (auto &child : vector<TreeNode *> {node->left, node->right}) {
                if (child) {
                    graph[node->val].push_back(child->val);
                    graph[child->val].push_back(node->val);
                    dfs(child);
                }
            }
        };

        dfs(root);
        queue<vector<int>> que;
        que.push({start, 0});
        unordered_set<int> visited;
        visited.insert(start);
        int time = 0;
        while (!que.empty()) {
            auto arr = que.front();
            que.pop();
            int node_val = arr[0];
            time = arr[1];
            for (auto child_val : graph[node_val]) {
                if (!visited.count(child_val)) {
                    que.push({child_val, time + 1});
                    visited.insert(child_val);
                }
            }
        }
        return time;
    }
};

int main() {

    return 0;
}