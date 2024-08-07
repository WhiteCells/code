#include "../../head_file.h"

/*
problme: 

url: 
 */

class Solution {
public:
    vector<int> postorder(Node* root) {
        dfs(root);
        return res;
    }
    void dfs(Node *root) {
        if (!root) {
            return;
        }
        for (const auto &node : root->children) {
            dfs(node);
        }
        res.push_back(root->val);
    }
    vector<int> res;
};

int main() {
    
    return 0;
}