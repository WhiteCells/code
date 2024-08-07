#include "../../head_file.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) :val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) :val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<ListNode*> s1, s2;
        while (l1) {
            s1.push(l1);
            l1 = l1->next;
        }
        while (l2) {
            s2.push(l2);
            l2 = l2->next;
        }

        int bit = 0;
        stack<int> s;

        while (!s1.empty() || !s2.empty()) {
            int l1_val = s1.empty() ? 0 : s1.top()->val;
            int l2_val = s2.empty() ? 0 : s2.top()->val;
            int sum = l1_val + l2_val + bit;
            s.push(sum % 10);
            bit = sum / 10;
            if (!s1.empty()) {
                s1.pop();
            }
            if (!s2.empty()) {
                s2.pop();
            }
        }
        if (bit > 0) {
            s.push(bit);
        }

        ListNode* head = new ListNode(0), * cur = head;
        while (!s.empty()) {
            ListNode* node = new ListNode(s.top());
            cur->next = node;
            cur = cur->next;
            s.pop();
        }
        return head->next;
    }
};


int main() {
    Solution s;
    // ListNode node1_4(3);
    // ListNode node1_3(4, &node1_4);
    // ListNode node1_2(2, &node1_3);
    // ListNode node1_1(7, &node1_2);

    // ListNode node2_3(4);
    // ListNode node2_2(6, &node2_3);
    // ListNode node2_1(5, &node2_2);

    ListNode node1_1(5);
    ListNode node2_1(5);

    ListNode* head = s.addTwoNumbers(&node1_1, &node2_1);
    ListNode* cur = head;

    while (cur) {
        cout << cur->val << " ";
        cur = cur->next;
    }
    return 0;
}