#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/insert-greatest-common-divisors-in-linked-list/
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 最大公倍数
// 最小公约数
class Solution {
public:
    ListNode *insertGreatestCommonDivisors(ListNode *head) {
        ListNode *cur = head;
        while (cur->next) {
            ListNode *nxt = cur->next;
            int tmp = nxt->val, a = cur->val, b = nxt->val;
            while (a % b) {
                tmp = a % b;
                a = b;
                b = tmp;
            }
            cur->next = new ListNode(tmp);
            cur->next->next = nxt;
            cur = nxt;
        }
        return head;
    }
};

void initList(ListNode *&head, vector<int> &v) {
    ListNode *cur = nullptr;
    for (const auto &ele : v) {
        if (!head) {
            head = cur = new ListNode(ele);
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
    cout << endl;
}

int main() {
    vector<int> v {18, 6, 10, 3};
    ListNode *head = nullptr;
    initList(head, v);
    ListNode *res = Solution().insertGreatestCommonDivisors(head);
    printList(res);
    return 0;
}