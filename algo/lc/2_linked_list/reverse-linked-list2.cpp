#include "../../head_file.h"

/*
problme:

url:
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int val) : val(val), next(nullptr) {}
};

class Solution {
public:
    ListNode *reverseList(ListNode *head) {
        
    }
};

class List {

public:
    List() : head_(nullptr), size_(0) {

    }

    List(const initializer_list<int> &list) : head_(nullptr), size_(0) {
        Node *cur = head_;
        for (const auto &val : list) {
            if (!head_) {
                cur = head_ = new Node(val);
            } else {
                cur->next_ = new Node(val);
                cur = cur->next_;
            }
            ++size_;
        }
    }

    ~List() {}

    void insert(initializer_list<int> list) {
        Node *cur = head_;
        while (cur->next_) {
            cur = cur->next_;
        }
        for (const auto &val : list) {
            cur->next_ = new Node(val);
            cur = cur->next_;
            ++size_;
        }
    }

    void addAtTail(int val) {
        if (!head_) {
            head_ = new Node(val);
        } else {
            Node *cur = head_;
            while (cur->next_) {
                cur = cur->next_;
            }
            cur->next_ = new Node(val);
        }
        ++size_;
    }

    void deleteAtTail() {
        if (!head_) {
            return;
        }
        Node *cur = head_;
        while (cur && cur->next_) {
            cur = cur->next_;
        }
        delete cur->next_;
        --size_;
    }

    void destory() {
        if (!size_) {
            return;
        }
        Node *cur = head_;
        while (cur) {
            Node *tmp = cur->next_;
            delete cur;
            cur = tmp;
        }
        size_ = 0;
    }

    void print() {
        if (!size_) {
            return;
        }
        Node *cur = head_;
        while (cur) {
            cout << cur->val_;
            cur = cur->next_;
        }
        cout << endl;
    }

private:
    struct Node {
        int val_;
        Node *next_;
        Node(int val) : val_(val) {}
    };
    Node *head_;
    unsigned size_;
};

int main() {
    // ::List list;
    // list.insert({1, 2, 3});
    // list.print();
    // // list.destory();
    // list.print();

    ::List list;
    list.addAtTail(1);
    list.print();
    // list.insert({4, 5, 6});
    // list.print();
    // list.destory();
    return 0;
}