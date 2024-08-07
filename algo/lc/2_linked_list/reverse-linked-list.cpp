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
    ListNode(): val(0), next(nullptr) {}
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode* next): val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // 这个链表是不带虚拟头结点的
        ListNode* pre = nullptr;
        ListNode* cur = head;
        ListNode* temp = nullptr;
        while (cur) {
            temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        return pre;
    }
};

class Solution2 {
public:
    ListNode* reverse(ListNode* pre, ListNode* cur) {
        if (cur == NULL) return pre;
        ListNode* temp = cur->next;
        cur->next = pre;
        return reverse(cur, temp);
    }
    ListNode* reverseList(ListNode* head) {
        return reverse(NULL, head);
    }
};

class Solution2_1 {
public:
    ListNode* reverse(ListNode* pre, ListNode* cur) {
        if (!cur) return pre;
        ListNode* temp = cur->next;
        cur->next = pre;
        return reverse(cur, temp);
    }
    ListNode* reverseList(ListNode* head) {
        return reverse(nullptr, head);
    }
};

class Solution3 {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head) return nullptr;
        if (!(head->next)) return head;
        ListNode* last = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return last;
    }
};

ListNode* CreateNode(int val) {
    return new ListNode(val, nullptr);
}

ListNode* CreateList() {
    int n = 0, val = 0;
    ListNode* head = new ListNode();
    ListNode* node = nullptr;
    ListNode* cur_head = head;
    cout << "链表长度:";
    cin >> n;
    while (n--) {
        cout << "链表的值:";
        cin >> val;
        node = CreateNode(val);
        cur_head->next = node;
        cur_head = cur_head->next;
    }
    return head;
}

// 创建不带虚拟头结点的链表
ListNode* CreateNoHeadList() {
    int n = 0, val = 0, i = 0;
    cin >> n;
    ListNode* head = new ListNode();
    ListNode* cur_head = head;
    while (n--) {
        if (!i) {
            i = 1;
            cin >> val;
            head->val = val;
            continue;
        }
        cin >> val;
        ListNode* node = CreateNode(val);
        cur_head->next = node;
        cur_head = cur_head->next;
    }
    return head;
}

void PrintList(ListNode* node) {
    while (node) {
        cout << node->val << " ";
        node = node->next;
    }
    cout << endl;
}

int main() {
    ListNode* list = CreateNoHeadList();
    PrintList(list);
    Solution3 s;
    ListNode* retlist = s.reverseList(list);
    PrintList(retlist);
    return 0;
}