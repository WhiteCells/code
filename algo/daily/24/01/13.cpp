#include "../../head_file.h"

/*
problme:

url:
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        if (!head) {
            return head;
        }
        ListNode *res = new ListNode(head->val);
        ListNode *cur = res;
        while (head) {
            ListNode *tmp = head->next;
            while (tmp && head->val == tmp->val) {
                tmp = tmp->next;
            }
            if (!tmp) {
                break;
            }
            head = tmp;
            cur->next = new ListNode(tmp->val);
            cur = cur->next;
        }
        return res;
    }
};

void initList(ListNode *&head, vector<int> &v) {
    ListNode *cur = head;
    for (const auto &ele : v) {
        if (!head) {
            cur = head = new ListNode(ele);
        } else {
            cur->next = new ListNode(ele);
            cur = cur->next;
        }
    }
}

void printList(ListNode *head) {
    while (head) {
        cout << head->val << ' ';
        head = head->next;
    }
    cout << '\n';
}

void destructList(ListNode *&head) {
    while (head) {
        ListNode *tmp = head->next;
        delete head;
        head = tmp;
    }
}

int main() {
    ListNode *head = nullptr;
    // vector<int> v {1, 1, 2};
    vector<int> v {1, 1, 2, 3, 3};
    initList(head, v);
    printList(head);

    ListNode *res = Solution().deleteDuplicates(head);
    printList(res);

    destructList(res);
    destructList(head);
    return 0;
}