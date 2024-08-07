#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int val) : val(val), next(nullptr) {}
    ListNode(int val, ListNode* next) : val(val), next(nullptr) {}
};


class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        ListNode* fast = head, * slow = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) {
                ListNode* p = head;
                while (p != slow) {
                    p = p->next;
                    slow = slow->next;
                }
                return p;
            }
        }
        return nullptr;
    }
};

class Solution2 {
public:
    ListNode* detectCycle(ListNode* head) {
        while (head) {
            if (1e6 == head->val) {
                return head;
            }
            head->val = 1e6;
            head = head->next;
        }
        return nullptr;
    }
};


int main() {
    Solution2 s;

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
    cur->next = head->next;

    cout << s.detectCycle(head)->val << ' ';

    return 0;
}