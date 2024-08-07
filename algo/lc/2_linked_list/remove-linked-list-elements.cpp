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

typedef struct ListNode {
    int val;
    struct ListNode* next;
    ListNode();
    ListNode(int x);
    ListNode(int x, ListNode* next);
} ListNode;

ListNode::ListNode(): val(0), next(nullptr) {}

ListNode::ListNode(int x): val(x), next(nullptr) {}

ListNode::ListNode(int x, ListNode* next): val(x), next(next) {}

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        // 删除头结点的 val == val
        // 先判断头结点是否为空，再判断头结点 val 是否等于 val
        while (head != nullptr && head->val == val) {
            ListNode* temp = head; // 临时指针变量接管 头结点
            head = head->next; // 更改头结点的指向
            delete temp; // 删除头结点
        }

        // 需要知道被删除结点的上一个结点
        ListNode* cur_node = head;
        // 先判断当前结点是否为空，再判断下一个结点是否为空
        while (cur_node != nullptr && cur_node->next != nullptr) {
            // 删除非头结点 val == val
            if (cur_node->next->val == val) {
                ListNode* temp = cur_node->next; // 临时指针变量接管 非头结点
                cur_node->next = cur_node->next->next; // 被删除结点的前一个结点指向被删除结点的后一个结点
                delete temp; // 删除非头结点
            }
            // 不相等的时候 cur_node 向后移动
            else {
                cur_node = cur_node->next;
            }
        }
        return head;
    }
};

int main() {

    return 0;
}