#include "../../head_file.h"

/*
problme: 6914. 翻倍以链表形式表示的数字
给你一个 非空 链表的头节点 head ，表示一个不含前导零的非负数整数。
将链表 翻倍 后，返回头节点 head 。
输入：head = [1,8,9]
输出：[3,7,8]
解释：上图中给出的链表，表示数字 189 。返回的链表表示数字 189 * 2 = 378 。
数据范围：
    链表中节点的数目在范围 [1, 10^4] 内
    0 <= Node.val <= 9
    生成的输入满足：链表表示一个不含前导零的数字，除了数字 0 本身。
url: https://leetcode.cn/problems/double-a-number-represented-as-a-linked-list/
@Author: Eorys
@Date: 2023-08-14 09:23:58
@Last Modified by: Eorys
@Last Modified time: 2023-08-14 09:23:58
@Description:
*/

class ListNode {
public:
    int val;
    ListNode* next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int val): val(val), next(nullptr) {}
    ListNode(int val, ListNode* next): val(val), next(next) {}
};

// 栈
class Solution {
public:
    ListNode* doubleIt(ListNode* head) {
        ListNode* cur = head;
        stack<ListNode*> s;
        while (cur) {
            s.push(cur);
            cur = cur->next;
        }
        stack<ListNode*> s2;
        int carry = 0;
        while (!s.empty()) {
            int val = s.top()->val * 2 + carry;
            s.top()->val = val % 10;
            carry = val / 10;
            s2.push(s.top());
            s.pop();
        }
        if (carry) {
            s2.push(new ListNode(carry));
        }
        ListNode* res_head = nullptr;
        while (!s2.empty()) {
            if (!res_head) {
                res_head = cur = s2.top();
            }
            else {
                cur->next = s2.top();
                cur = cur->next;
            }
            s2.pop();
        }
        return res_head;
    }
};

// O(n)
// 考虑进位，按链表顺序遍历，当前值的下一个值大于 5，当前值进位 1
class Solution2 {
public:
    ListNode* doubleIt(ListNode* head) {
        if (head->val >= 5) {
            head = new ListNode(0, head);
        }
        ListNode* cur = head;
        while (cur) {
            cur->val = cur->val * 2 % 10;
            if (cur->next && cur->next->val >= 5) {
                ++cur->val; // 进位
            }
            cur = cur->next;
        }
        return head;
    }
};

void InitList(ListNode*& head);
void PrintList(ListNode* head);

int main() {
    ListNode* head1 = nullptr;
    InitList(head1);

    // Solution s;
    // ListNode* res_head = s.doubleIt(head1);
    // PrintList(res_head);

    // PrintList(head1);

    Solution2 s2;
    ListNode* res_head2 = s2.doubleIt(head1);
    PrintList(res_head2);

    return 0;
}

void PrintList(ListNode* head) {
    while (head) {
        cout << head->val << ' ';
        head = head->next;
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
        if (!head) {
            head = cur = new ListNode(val);
        }
        else {
            cur->next = new ListNode(val);
            cur = cur->next;
        }
    }
}