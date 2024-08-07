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
    TreeNode *reverseOddLevels(TreeNode *root) {
        queue<TreeNode *> q;
        q.emplace(root);
        bool flag = false;

    }
};

int main() {

    return 0;
}