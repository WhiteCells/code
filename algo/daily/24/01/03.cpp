#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/remove-nodes-from-linked-list/description/
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 单调栈 or 反转链表
class Solution {
public:
    ListNode *removeNodes(ListNode *head) {
        reverseList(head);
        ListNode *res = new ListNode(head->val);
        ListNode *cur = res;
        ListNode *pre = head;
        head = head->next;
        while (head) {
            if (head->val >= pre->val) {
                cur->next = new ListNode(head->val);
                cur = cur->next;
                pre = cur;
                head = head->next;
            } else {
                while (head && head->val < pre->val) {
                    head = head->next;
                }
                if (head) {
                    cur->next = new ListNode(head->val);
                    cur = cur->next;
                    head = head->next;
                    pre = cur;
                }
            }
        }
        reverseList(res);
        return res;
    }
private:
    void reverseList(ListNode *&head) {
        ListNode *pre = nullptr;
        ListNode *cur = head;
        while (cur) {
            ListNode *nxt = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nxt;
        }
        head = pre;
    }
};

ListNode *initList(vector<int> &v) {
    ListNode *head = nullptr;
    ListNode *cur = head;
    for (int i = 0; i < v.size(); ++i) {
        if (0 == i) {
            head = cur = new ListNode(v[i]);
        } else {
            cur->next = new ListNode(v[i]);
            cur = cur->next;
        }
    }
    return head;
}

void printList(ListNode *head) {
    while (head) {
        cout << head->val << ' ';
        head = head->next;
    }
    cout << '\n';
}

int main() {
    // [5,2,13,3,8]
    // vector<int> v {5, 2, 13, 3, 8};
    vector<int> v {577, 95, 436, 700, 467, 568, 389, 376, 830, 361, 818, 517, 290, 191, 596, 644,
        425, 308, 825, 555, 583, 996, 630, 886, 382, 354, 455, 883, 581, 408, 619, 531, 618, 355,
        14, 653, 638, 589, 271, 430, 519, 517, 851, 875, 69, 496, 924, 680, 753, 287, 496, 166,
        300, 126, 935, 96, 537, 394, 634, 270, 72, 688, 158, 930, 534, 746, 520, 649, 318, 632, 592,
        732, 670, 291, 151, 128, 841, 680, 158, 631, 196, 707, 439, 534, 666, 22, 626, 299, 121, 346,
        11, 426, 827, 459, 748, 551, 561, 110, 192, 103, 165, 111, 798, 138, 665, 289, 874, 12, 99, 201,
        432, 653, 239, 418, 941, 575, 441, 751, 571, 815, 535, 818, 301, 914, 106, 633, 734, 836, 931,
        515, 673, 559, 464, 644, 305, 337, 242, 421, 342, 690, 152, 739, 816, 974, 901, 529, 851, 213, 90,
        640, 301, 747, 735, 536, 428, 816, 442, 156, 660, 680, 617, 659, 676, 914, 791, 673, 569, 414, 254,
        185, 42, 21, 708, 798, 22, 40, 18, 433, 975, 743, 6, 103, 697, 372, 824, 382, 365, 500, 725, 441, 839,
        22, 439, 320, 738, 769, 290, 243, 247, 821, 812, 293, 461, 324, 73, 923, 974, 909, 585, 832, 320, 136,
        463, 920, 464, 260, 862, 617, 422, 922, 697, 972, 888, 8, 116, 349, 655, 941, 941, 813, 591, 444, 321,
        922, 379, 761, 566, 273, 706, 453, 568, 268};
    ListNode *head = initList(v);
    // printList(head);
    // [996,975,974,972,941,941,922,761, 706, 568,268]
    ListNode *res = Solution().removeNodes(head);
    printList(res);
    return 0;
}