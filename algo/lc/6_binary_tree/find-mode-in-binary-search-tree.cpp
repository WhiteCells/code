#include "D:\distake\Coding\head_file.h"

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right): val(x), left(left), right(right) {}
};

class Solution {
public:
    static bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }
    void traversal(TreeNode* root, map<int, int>& countMap) {
        if (!root) {
            return;
        }
        traversal(root->left, countMap);
        countMap[root->val]++;
        traversal(root->right, countMap);
    }
    vector<int> findMode(TreeNode* root) {
        map<int, int> countMap;
        traversal(root, countMap);
        // for (map<int, int>::iterator it = countMap.begin(); it != countMap.end(); ++it) {
        //     cout << it->first << " " << it->second << endl;
        // }
        vector<pair<int, int>> v(countMap.begin(), countMap.end());
        sort(v.begin(), v.end(), cmp);
        vector<int> rev;
        rev.push_back(v[0].first);
        for (int i = 1; i < (int)v.size(); ++i) {
            if (v[i].second == v[0].second) {
                rev.push_back(v[i].first);
            }
            else {
                break;
            }
        }
        return rev;
    }
};

class Solution2 {
public:
    void traversal(TreeNode* root, vector<int>& v) {
        if (!root) {
            return;
        }
        // 利用中序遍历可以获取有序数列
        traversal(root->left, v);

        if (!pre) { // 上一次遍历的结点为空
            count = 1;
        }
        else if (pre->val == root->val) { // 遍历到的结点等于上一次遍历到的结点
            ++count;
        }
        else { // 不等于上一次遍历到的结点
            count = 1;
        }
        if (maxCount == count) {
            v.push_back(root->val);
        }
        if (maxCount < count) {
            v.clear();
            v.push_back(root->val);
            maxCount = count;
        }
        pre = root; // 更新上一次遍历到结点

        traversal(root->right, v);
    }
    vector<int> findMode(TreeNode* root) {
        vector<int> rev;
        traversal(root, rev);
        return rev;
    }
private:
    TreeNode* pre = nullptr;
    int count = 0;
    int maxCount = 0;
};


int main() {
    TreeNode node1(1);
    TreeNode node2(3);
    TreeNode node3(3, &node1, &node2);
    TreeNode node4(4);
    TreeNode node5(5, &node4, nullptr);
    TreeNode node6(6, &node5, &node3);
    Solution2 s;
    vector<int> rev = s.findMode(&node6);
    for (auto& val : rev) {
        cout << val << " ";
    }
    return 0;
}