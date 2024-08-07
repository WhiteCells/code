#include <iostream>
#include <stack>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int val) : val(val), next(nullptr) {}
    ListNode(int val, ListNode* next) : val(val), next(nullptr) {}
}*list;

class Solution {
public:
    void reorderList(ListNode* head) {
        stack<ListNode*> s;
        ListNode* p = head;
        while (p) {
            s.push(p);
            p = p->next;
        }
        ListNode* cur = head;
        int n = s.size();
        for (int i = 0; cur && i < n; ++i) {
            if (0 == i % 2) {
                s.top()->next = cur->next;
                cur->next = s.top();
                s.pop();
            }
            cur = cur->next;
        }
        cur->next = nullptr;
    }
};

int main() {
    Solution s;
    ListNode node1(1);
    ListNode node2(2);
    ListNode node3(3);
    ListNode node4(4);

    ListNode* head = &node1;
    
    ListNode* cur = head;
    cur->next = &node2;
    cur = cur->next;

    cur->next = &node3;
    cur = cur->next;

    cur->next = &node4;
    cur = cur->next;

    s.reorderList(head);
    ListNode* p = head;
    while (p) {
        cout << p->val << ' ';
        p = p->next;
    }
    return 0;
}

