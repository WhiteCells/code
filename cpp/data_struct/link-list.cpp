#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int val) : val(val), next(nullptr) {}
    ListNode(int val, ListNode *next) : val(val), next(next) {}
};

void ReferenceTraversal(ListNode *&head) {
    ListNode *cur = head;
    while (cur) {
        cout << cur->val << ' ';
        cur = cur->next;
    }
    cout << '\n';
}

// 非引用则不能改变地址，只能改变值
void reverseList(ListNode *&head) {
    ListNode *cur = head;
    ListNode *pre = nullptr;
    while (cur) {
        ListNode *nxt = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nxt;
    }
    head = pre;
}

// 节点指针域被修改
ListNode *reverseList(ListNode *head, int) {
    ListNode *cur = head;
    ListNode *pre = nullptr;
    while (cur) {
        ListNode *nxt = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nxt;
    }
    return pre;
}

void initList(ListNode *&head) {
    ListNode *cur = nullptr;
    int len = 0;
    cin >> len;
    while (len--) {
        int val = 0;
        cin >> val;
        if (!cur) {
            head = cur = new ListNode(val);
        } else {
            cur->next = new ListNode(val);
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

void listTest() {
    ListNode *head = nullptr;
    initList(head);
    printList(head);

    // reverseList(head);
    // printList(head);

    auto p = reverseList(head, 1);
    printList(p);
    printList(head);
}

// ability to modify test node values, but do not modify test1 node address
void foo1(ListNode *node) {
    // node = nullptr;

    // node->next = nullptr;
    // node->val = 10;

    ListNode *cur = node;
    cur->val = 10;
    cur->next = new ListNode(20);
    cout << "foo1 node->val: " << node->val << endl;
    if (!node->next) {
        cout << "foo1 node->next is empty" << endl;
    } else {
        cout << "foo1 node->next is not empty" << endl;
    }
}

void test1() {
    ListNode *node = new ListNode(1);

    foo1(node);
    cout << "test1 node->val: " << node->val << endl;
    if (!node->next) {
        cout << "test1 node->next is empty" << endl;
    } else {
        cout << "test1 node->next is not empty" << endl;
        cout << "test1 node->next->val: " << node->next->val << endl;
    }
}

// ability to modify test2 node address and test2 node values
void foo2(ListNode *&node) {
    node->val = 100;
    ListNode *new_node = new ListNode(200);
    node->next = new_node;
}

void test2() {
    ListNode *node = new ListNode(1);

    foo2(node);
    cout << "test2 node->val: " << node->val << endl;
    if (!node) {
        cout << "test2 node->next is empty" << endl;
    } else {
        cout << "test2 node->next is not empty" << endl;
        cout << "test2 node->next->val: " << node->next->val << endl;
    }
}

int main() {
    listTest();
    // test1();
    // test2();
    return 0;
}