#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int val): val(val), next(nullptr) {}
    ListNode(int val, ListNode* next): val(val), next(next) {}
};



class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) {
            return nullptr;
        }
        struct Cmp {
            bool operator()(ListNode* list1, ListNode* list2) {
                return list1->val > list2->val;
            }
        };
        priority_queue<ListNode*, vector<ListNode*>, Cmp> q;
        for (const auto& head : lists) {
            if (head) {
                q.push(head);
            }
        }
        ListNode* dummy_head = new ListNode;
        ListNode* cur = dummy_head;
        while (!q.empty()) {
            ListNode* top_node = q.top();
            // cur->next = new ListNode(top_node->val);
            cur->next = top_node;
            cur = cur->next;
            q.pop();
            if (top_node->next) {
                q.push(top_node->next);
            }
        }
        ListNode* res_head = dummy_head->next;
        delete dummy_head;
        return res_head;
    }
};

int main() {
    Solution s;
    vector<ListNode*> lists;
    int n = 0;
    cin >> n;
    while (n--) {
        ListNode* head = nullptr;
        ListNode* cur = nullptr;
        int x = 0;
        cin >> x;
        while (x--) {
            int val = 0;
            cin >> val;
            if (!head) {
                head = new ListNode(val);
                cur = head;
                continue;
            }
            ListNode* node = new ListNode(val);
            cur->next = node;
            cur = cur->next;
        }
        lists.push_back(head);
    }
    ListNode* res_head = s.mergeKLists(lists);
    while (res_head) {
        cout << res_head->val << ' ';
        res_head = res_head->next;
    }
    return 0;
}