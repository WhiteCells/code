#include <iostream>

using namespace std;


struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int val) : val(val), next(nullptr) {}
    ListNode(int val, ListNode* next) : val(val), next(next) {}
};

// 空间 O(n)
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (!list1 || !list2) {
            return list2 ? list2 : list1;
        }
        ListNode* head = new ListNode;
        ListNode* cur = head;
        while (list1 && list2) {
            if (list1->val < list2->val) {
                cur->next = new ListNode(list1->val);
                list1 = list1->next;
            }
            else {
                cur->next = new ListNode(list2->val);
                list2 = list2->next;
            }
            cur = cur->next;
        }
        if (list1) {
            while (list1) {
                cur->next = new ListNode(list1->val);
                cur = cur->next;
                list1 = list1->next;
            }
        }
        else if (list2) {
            while (list2) {
                cur->next = new ListNode(list2->val);
                cur = cur->next;
                list2 = list2->next;
            }
        }
        return head->next;
    }
};


// 空间 O(1)
class Solution2 {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (!list1 || !list2) {
            return list2 ? list2 : list1;
        }
        ListNode* node = new ListNode;
        node->val = list1->val < list2->val ? list1->val : list2->val;
        node->next = list1->val < list2->val ? mergeTwoLists(list1->next, list2) : mergeTwoLists(list1, list2->next);
        return node;
    }
};

class Solution3 {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (!list1 || !list2) {
            return list2 ? list2 : list1;
        }
        ListNode* node = list1->val < list2->val ? list1 : list2;
        node->next = list1->val < list2->val ? mergeTwoLists(list1->next, list2) : mergeTwoLists(list1, list2->next);
        return node;
    }
};

int main() {
    // list1
    int len1 = 0;
    cin >> len1;
    ListNode* head1 = new ListNode();
    ListNode* cur1 = head1;
    while (len1--) {
        int val = 0;
        cin >> val;
        cur1->next = new ListNode(val);
        cur1 = cur1->next;
    }
    // list2
    int len2 = 0;
    cin >> len2;
    ListNode* head2 = new ListNode();
    ListNode* cur2 = head2;
    while (len2--) {
        int val = 0;
        cin >> val;
        cur2->next = new ListNode(val);
        cur2 = cur2->next;
    }
    Solution3 s;
    ListNode* resp = s.mergeTwoLists(head1->next, head2->next);
    while (resp) {
        cout << resp->val << ' ';
        resp = resp->next;
    }
    return 0;
}