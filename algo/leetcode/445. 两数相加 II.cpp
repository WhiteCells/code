#include "../head_file.h"

/*
problme: 445. 两数相加 II
给定两个 非空链表 l1和 l2 来代表两个非负整数。数字最高位位于链表开始位置。它们的每个节点只存储一位数字。将这两数相加会返回一个新的链表。
可以假设除了数字 0 之外，这两个数字都不会以零开头。
输入：l1 = [7,2,4,3], l2 = [5,6,4]
输出：[7,8,0,7]
数据范围：
    链表的长度范围为 [1, 100]
    0 <= node.val <= 9
    输入数据保证链表代表的数字无前导 0
url: https://leetcode.cn/problems/add-two-numbers-ii/
@Author: Eorys
@Date: 2023-08-14 18:57:00
@Last Modified by: Eorys
@Last Modified time: 2023-08-14 18:57:00
@Description:
*/

struct ListNode {
    int val;
    ListNode* next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int val): val(val), next(nullptr) {}
    ListNode(int val, ListNode* next): val(val), next(next) {}
};

// 翻转链表
class Solution {
private:
    // O(n)
    void ReverseList(ListNode*& head) {
        ListNode* cur = head;
        ListNode* pre = nullptr;
        while (cur) {
            ListNode* tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        head = pre;
    }
public:
    // 32ms
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ReverseList(l1);
        ReverseList(l2);
        int carry = 0;
        ListNode* res_head = nullptr, *cur = res_head;
        while (l1 || l2) {
            int l1_val = l1 ? l1->val : 0;
            int l2_val = l2 ? l2->val : 0;
            int val = l1_val + l2_val + carry;
            if (!res_head) {
                res_head = cur = new ListNode(val % 10);
            }
            else {
                cur->next = new ListNode(val % 10);
                cur = cur->next;
            }
            carry = val / 10;
            if (l1) {
                l1 = l1->next;
            }
            if (l2) {
                l2 = l2->next;
            }
        }
        if (carry) {
            cur->next = new ListNode(carry);
        }
        ReverseList(res_head);
        return res_head;
    }
};

// 栈
class Solution2 {
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
        int carry = 0;
        stack<ListNode*> s;
        while (!s1.empty() || !s2.empty()) {
            int l1_val = s1.empty() ? 0 : s1.top()->val;
            int l2_val = s2.empty() ? 0 : s2.top()->val;
            int val = l1_val + l2_val + carry;
            carry = val / 10;
            s.push(new ListNode(val % 10));
            if (!s1.empty()) {
                s1.pop();
            }
            if (!s2.empty()) {
                s2.pop();
            }
        }
        if (carry) {
            s.push(new ListNode(carry));
        }
        ListNode* res_head = nullptr, * cur = res_head;
        while (!s.empty()) {
            if (!cur) {
                res_head = cur = s.top();
            }
            else {
                cur->next = s.top();
                cur = cur->next;
            }
            s.pop();
        }
        return res_head;
    }
};

void PrintList(ListNode* head);
void InitList(ListNode*& head);

/*
4
7 2 4 3
3
5 6 4
*/

int main() {
    ListNode* head1 = nullptr, * head2 = nullptr;
    InitList(head1);
    InitList(head2);

    Solution s;
    ListNode* res_head = s.addTwoNumbers(head1, head2);
    PrintList(res_head);

    PrintList(head1);
    PrintList(head2);

    Solution2 s2;
    ListNode* res_head2 = s2.addTwoNumbers(head1, head2);
    PrintList(res_head2);

    PrintList(head1);
    PrintList(head2);
    return 0;
}

void PrintList(ListNode* head) {
    ListNode* cur = head;
    while (cur) {
        cout << cur->val << ' ';
        cur = cur->next;
    }
    cout << '\n';
}

void InitList(ListNode*& head) {
    ListNode* cur = head;
    int len = 0;
    cin >> len;
    while (len--) {
        int val = 0;
        cin >> val;
        if (!cur) {
            head = cur = new ListNode(val);
        }
        else {
            cur->next = new ListNode(val);
            cur = cur->next;
        }
    }
}