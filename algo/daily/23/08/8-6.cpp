#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(val), next(next) {}
    ListNode(int val) : val(val), next(nullptr) {}
    ListNode(int val, ListNode* next) : val(val), next(next) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (!head) {
            return nullptr;
        }
        ListNode* new_head = new ListNode(0, head);
        ListNode* cur = new_head;
        // 至少要有两个节点
        while (cur->next && cur->next->next) {
            // 暂存节点
            ListNode* node1 = cur->next;
            ListNode* node3 = cur->next->next->next;
            // 连接节点
            cur->next = cur->next->next;
            cur->next->next = node1;
            cur->next->next->next = node3;
            // 更新指针
            cur = cur->next->next;
        }
        ListNode* ans = new_head->next;
        delete new_head;
        return ans;
    }
};

class Solution2 {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* node = head;
        // 如果有两个数，则更换头节点
        if (head && head->next) {
            head = node->next;
        }
        // 有两个数
        while (node && node->next) {
            ListNode* tmp = node->next->next;
            node->next->next = node;
            node->next = tmp && tmp->next ? tmp->next : tmp;
            node = tmp;
        }
        return head;
    }
};

int main() {
    ListNode* head = new ListNode;
    int n = 0;
    cin >> n;
    ListNode* cur = head;
    while (n--) {
        int val = 0;
        cin >> val;
        ListNode* node = new ListNode(val);
        cur->next = node;
        cur = cur->next;
    }
    Solution s;
    ListNode* res_list = s.swapPairs(head->next);
    while (res_list) {
        cout << res_list->val << ' ';
        res_list = res_list->next;
    }
    return 0;
}