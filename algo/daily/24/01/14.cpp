#include "../../head_file.h"

/*
problme:
给定一个已排序的链表的头 head ， 删除原始链表中所有重复数字的节点，只留下不同的数字 。返回 已排序的链表 。
输入：head = [1,2,3,3,4,4,5]
输出：[1,2,5]

链表中节点数目在范围 [0, 300] 内
-100 <= Node.val <= 100
题目数据保证链表已经按升序 排列

url: https://leetcode.cn/problems/remove-duplicates-from-sorted-list-ii/description/
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
        if (!head || !head->next) {
            return head;
        }
        ListNode *res = new ListNode(), *cur = res;
        while (head && head->next) {
            if (head->val == head->next->val) {
                while (head && head->next && head->val == head->next->val) {
                    head = head->next;
                }
            } else {
                cur->next = new ListNode(head->val);
                cur = cur->next;
            }
            int pre = head->val;
            head = head->next;
            // 最后一个位置
            if (head && !head->next && head->val != pre) {
                cur->next = new ListNode(head->val);
            }
        }
        return res->next;
    }
};

void initList(ListNode *&head, vector<int> &v) {
    ListNode *cur = head;
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
    vector<int> v {1, 2, 3, 3, 4, 4, 5};
    // vector<int> v {1, 1};
    ListNode *head = nullptr;
    initList(head, v);
    printList(head);

    auto res = Solution().deleteDuplicates(head);
    printList(res);

    destructList(head);
    destructList(res);
    return 0;
}