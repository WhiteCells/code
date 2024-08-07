#include "../head_file.h"
/*
 * @lc app=leetcode.cn id=234 lang=cpp
 *
 * [234] 回文链表
 *
 * https://leetcode.cn/problems/palindrome-linked-list/description/
 *
 * algorithms
 * Easy (53.76%)
 * Likes:    1831
 * Dislikes: 0
 * Total Accepted:    666.8K
 * Total Submissions: 1.2M
 * Testcase Example:  '[1,2,2,1]'
 *
 * 给你一个单链表的头节点 head ，请你判断该链表是否为回文链表。如果是，返回 true ；否则，返回 false 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：head = [1,2,2,1]
 * 输出：true
 *
 *
 * 示例 2：
 *
 *
 * 输入：head = [1,2]
 * 输出：false
 *
 *
 *
 *
 * 提示：
 *
 *
 * 链表中节点数目在范围[1, 10^5] 内
 * 0 <= Node.val <= 9
 *
 *
 *
 *
 * 进阶：你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？
 *
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// @lc code=start
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
class Solution {
public:
    bool isPalindrome(ListNode *head) {
        // find middle point, slow is midpoint
        ListNode *fast = head, *slow = head;
        // number of nodes to be compared
        int len = 0;
        // fast and slow pointer
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            ++len;
        }
        // fast is not null and fast->next is null, slow = slow->next
        if (fast && !fast->next) {
            slow = slow->next;
        }
        // reverse slow point after list
        ListNode *pre = nullptr;
        ListNode *tmp = nullptr;
        while (slow) {
            tmp = slow->next;
            slow->next = pre;
            pre = slow;
            slow = tmp;
        }
        // double pointer
        ListNode *left = head, *right = pre;
        while (len--) {
            if (left->val != right->val) {
                return false;
            }
            left = left->next;
            right = right->next;
        }
        return true;
    }
};
// @lc code=end


int main() {
    Solution s;
    ListNode *head = new ListNode(1);
    head->next = new ListNode(1);
    head->next->next = new ListNode(2);
    head->next->next->next = new ListNode(1);
    // head->next->next->next->next = new ListNode(2);
    // head->next->next->next->next->next = new ListNode(1);
    cout << s.isPalindrome(head) << endl;
    return 0;
}