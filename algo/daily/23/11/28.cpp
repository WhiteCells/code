#include "../../head_file.h"

/*
problme:

url: https://leetcode.cn/problems/design-front-middle-back-queue/description
 */

class FrontMiddleBackQueue {
public:
    FrontMiddleBackQueue() : head(nullptr), tail(nullptr), midd(nullptr), size(0) {}

    void pushFront(int val) {
        Node *node = new Node(val);
        if (!head) {
            tail = midd = head = node;
        } else {
            head->prev = node;
            node->next = head;
            head = node;
            if (!(size & 1)) {
                midd = midd->prev;
            }
        }
        ++size;
    }

    void pushMiddle(int val) {
        Node *node = new Node(val);
        if (!head) {
            tail = midd = head = node;
        } else {
            if (midd == head) {
                node->next = head;
                head->prev = node;
                head = node;
            } else {
                node->next = midd;
                midd->prev->next = node;
                node->prev = midd->prev;
                midd->prev = node;
            }
            if (!(size & 1)) {
                midd = midd->prev;
            }
        }
        ++size;
    }

    void pushBack(int val) {
        Node *node = new Node(val);
        if (!head) {
            tail = midd = head = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = tail->next;
            if (size & 1) {
                midd = midd->next;
            }
        }
        ++size;
    }

    int popFront() {
        if (!head) {
            return -1;
        }
        int res = head->val;
        if (size == 1) {
            head = midd = tail = nullptr;
            --size;
            return res;
        } else if (size & 1) {
            midd = midd->next;
        }
        Node *tmp = head->next;
        delete head;
        head = tmp;
        --size;
        return res;
    }

    int popMiddle() {
        if (!head) {
            return -1;
        }
        int res = midd->val;
        int res2 = midd->prev->val;
        if (size == 1) {
            head = midd = tail = nullptr;
            --size;
            return res;
        } else if (size == 2) {
            delete head;
            head = midd;
            --size;
            return res2;
        }
        Node *tmpMidd = midd;
        if (size & 1) {
            tmpMidd = midd->next;
        } else {
            tmpMidd = midd->prev;
        }
        Node *tmpPrev = midd->prev;
        Node *tmpNext = midd->next;
        delete midd;
        tmpPrev->next = tmpNext;
        tmpNext->prev = tmpPrev;
        midd = tmpMidd;
        --size;
        return size & 1 ? res2 : res;
    }

    int popBack() {
        if (!head) {
            return -1;
        }
        int res = tail->val;
        if (size == 1) {
            head = midd = tail = nullptr;
            --size;
            return res;
        }
        if (!(size & 1)) {
            midd = midd->prev;
        }
        Node *tmp = tail->prev;
        delete tail;
        tail = tmp;
        --size;
        return res;
    }
private:
    struct Node {
        int val;
        Node *prev;
        Node *next;
        Node(int v) : val(v), prev(nullptr), next(nullptr) {}
        Node(int v, Node *p, Node *n) : val(v), prev(p), next(n) {}
    };
    Node *head;
    Node *tail;
    Node *midd;
    int size;
};

class FrontMiddleBackQueue2 {
public:
    FrontMiddleBackQueue2() {}

    void pushFront(int val) {
        left.emplace_front(val);
    }

    void pushMiddle(int val) {
        right.emplace_front(val);
    }

    void pushBack(int val) {
        right.emplace_back(val);
    }

    int popFront() {
        if (left.empty() && right.empty()) {
            return -1;
        }
        
        if (left.empty()) {
            balance();
            int res = left.front();
            left.pop_front();
            return res;
        }
        int res = left.front();
        left.pop_front();
        return res;
    }

    int popMiddle() {
        if (left.empty() && right.empty()) {
            return -1;
        }
        balance();
        int res = left.back();
        left.pop_back();
        return res;
    }

    int popBack() {
        if (left.empty() && right.empty()) {
            return -1;
        }
        if (right.empty()) {
            balance();
            int res = right.back();
            right.pop_back();
            return res;
        }
        int res = right.back();
        right.pop_back();
        return res;
    }
private:
    deque<int> left, right;
    void balance() {
        while (left.size() < right.size()) {
            left.emplace_back(right.front());
            right.pop_front();
        }
        while (left.size() > right.size()) {
            right.emplace_front(left.back());
            left.pop_back();
        }
    }
};

class FrontMiddleBackQueue3 {
public:
    FrontMiddleBackQueue3() {}

    void pushFront(int val) {
        left.push_front(val);
        // 左边比右边多两个
        if (left.size() == right.size() + 2) {
            right.push_front(left.back());
            left.pop_back();
        }
    }

    void pushMiddle(int val) {
        // 左边比右边多一个
        if (left.size() == right.size() + 1) {
            right.push_front(left.back());
            left.pop_back();
        }
        left.push_back(val);
    }

    void pushBack(int val) {
        right.push_back(val);
        // 左边比右边少一个
        if (left.size() + 1 == right.size()) {
            left.push_back(right.front());
            right.pop_front();
        }
    }

    int popFront() {
        if (left.empty()) {
            return -1;
        }
        int res = left.front();
        left.pop_front();
        // 左边比右边少一个
        if (left.size() + 1 == right.size()) {
            left.push_back(right.front());
            right.pop_front();
        }
        return res;
    }

    int popMiddle() {
        if (left.empty()) {
            return -1;
        }
        int res = left.back();
        left.pop_back();
        // 左边比右边少一个
        if (left.size() + 1 == right.size()) {
            left.push_back(right.front());
            right.pop_front();
        }
        return res;
    }

    int popBack() {
        if (left.empty()) {
            return -1;
        }
        int res = 0;
        if (right.empty()) {
            // 此时只有左边一个数值
            res = left.back();
            left.pop_back();
        } else {
            res = right.back();
            right.pop_back();
            if (left.size() == right.size() + 2) {
                right.push_front(left.back());
                left.pop_back();
            }
        }
        return res;
    }
private:
    deque<int> left, right;
};

int main() {
    FrontMiddleBackQueue2 q;
    q.pushFront(1);   // [1]
    q.pushBack(2);    // [1, 2]
    q.pushMiddle(3);  // [1, 3, 2]
    q.pushMiddle(4);  // [1, 4, 3, 2]
    cout << q.popFront() << std::endl;     // 返回 1 -> [4, 3, 2]
    cout << q.popMiddle() << std::endl;    // 返回 3 -> [4, 2]
    cout << q.popMiddle() << std::endl;    // 返回 4 -> [2]
    cout << q.popBack() << std::endl;      // 返回 2 -> []
    cout << q.popFront() << std::endl;     // 返回 -1 -> [] （队列为空）

    // q.pushMiddle(1);
    // q.pushMiddle(2);
    // q.pushMiddle(3);
    // std::cout << q.popMiddle() << std::endl;
    // std::cout << q.popMiddle() << std::endl;
    // std::cout << q.popMiddle() << std::endl;

    // q.pushFront(1);
    // q.pushFront(2);
    // q.pushFront(3);
    // q.pushFront(4);
    // std::cout << q.popBack() << std::endl;
    // std::cout << q.popBack() << std::endl;
    // std::cout << q.popBack() << std::endl;
    // std::cout << q.popBack() << std::endl;
    
    return 0;
}