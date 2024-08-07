#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

#include <iostream>
#include <initializer_list>
#include <cstddef>

template<typename T>
class LinkList {
public:
    LinkList();
    LinkList(const std::initializer_list<T> &init_list);
    ~LinkList();

    void insertFront(const T &val);
    void insertBack(const T &val);
    void deleteByVal(const T &val);
    bool deleteByIdx(size_t idx);
    void deleteFront();
    void deleteBack();
    bool modifyByVal(const T &val);
    bool modifyByIdx(size_t idx);
    bool findByVal(const T &val);
    bool findByIdx(size_t idx);
    void print() const;

    size_t getSize() const;

private:
    struct ListNode {
        T val_;
        ListNode *next_;
        ListNode(int val) : val_(val), next_(nullptr) {}
        ListNode(int val, ListNode *next) : val_(val), next_(next) {}
    };
    size_t size_;
    ListNode *head_;
};

template<typename T>
inline LinkList<T>::LinkList() :
    size_(0),
    head_(nullptr) {

}

template<typename T>
inline LinkList<T>::LinkList(const std::initializer_list<T> &init_list) :
    head_(nullptr),
    size_(0) {

    ListNode *tmp = head_;
    for (const auto &val : init_list) {
        if (!tmp) {
            head_ = tmp = new ListNode(val);
        } else {
            tmp->next_ = new ListNode(val);
            tmp = tmp->next_;
        }
        ++size_;
    }
}

template<typename T>
inline LinkList<T>::~LinkList() {
    ListNode *delete_node = head_;
    while (delete_node) {
        ListNode *next_node = delete_node->next_;
        delete delete_node;
        delete_node = nullptr;
        delete_node = next_node;
    }
}

template<typename T>
inline void LinkList<T>::insertFront(const T &val) {
    if (!head_) {
        head_ = new ListNode(val);
    } else {
        ListNode *tmp = head_;
        head_ = new ListNode(val);
        head_->next_ = tmp;
    }
    ++size_;
}

template<typename T>
inline void LinkList<T>::insertBack(const T &val) {
    if (!head_) {
        head_ = new ListNode(val);
    } else {
        ListNode *tmp = head_;
        while (tmp && tmp->next_) {
            tmp = tmp->next_;
        }
        tmp->next_ = new ListNode(val);
    }
    ++size_;
}

// 没有空头节点不便于按值删除
template<typename T>
inline void LinkList<T>::deleteByVal(const T &val) {
    if (!head_) {
        return;
    }

    ListNode *virtual_head = new ListNode(0, head_);
    ListNode *tmp = virtual_head;
    while (tmp && tmp->next_) {
        bool flag = true;
        if (tmp->next_->val_ == val) {
            ListNode *delete_node = tmp->next_;
            tmp->next_ = delete_node->next_;
            delete delete_node;
            delete_node = nullptr;
            --size_;
            flag = false;
        }
        if (flag) {
            tmp = tmp->next_;
        }
    }
    head_ = virtual_head->next_;

    delete virtual_head;
    virtual_head = nullptr;
}

template<typename T>
inline bool LinkList<T>::deleteByIdx(size_t idx) {
    if (idx > getSize()) {
        idx = getSize() - 1;
    }
    if (idx == 0) {
        deleteFront();
        return false;
    }
    ListNode *cur = head_;
    for (size_t i = 0; i + 1 < idx; ++i) {
        cur = cur->next_;
    }
    ListNode *delete_node = cur->next_;
    cur->next_ = delete_node->next_;
    delete delete_node;
    --size_;
    return true;
}

template<typename T>
inline void LinkList<T>::deleteFront() {
    if (!head_) {
        return;
    }

    ListNode *delete_node = head_;
    head_ = delete_node->next_;
    delete delete_node;
    delete_node = nullptr;

    --size_;
}

template<typename T>
inline void LinkList<T>::deleteBack() {
    if (!head_) {
        return;
    }

    ListNode *tmp = head_;
    while (tmp && tmp->next_ && tmp->next_->next_) {
        tmp = tmp->next_;
    }

    ListNode *delete_node = tmp->next_;
    tmp->next_ = nullptr;

    delete delete_node;
    delete_node = nullptr;

    --size_;
}

template<typename T>
inline bool LinkList<T>::modifyByVal(const T &val) {
    return true;
}

template<typename T>
inline bool LinkList<T>::modifyByIdx(size_t idx) {
    return true;
}

template<typename T>
inline bool LinkList<T>::findByVal(const T &val) {
    return true;
}

template<typename T>
inline bool LinkList<T>::findByIdx(size_t idx) {
    return true;
}

template<typename T>
inline void LinkList<T>::print() const {
    if (!head_) {
        return;
    }
    int n = 0;
    ListNode *tmp = head_;
    while (tmp) {
        std::cout << tmp->val_ << ((++n < getSize()) ? "->" : "");
        tmp = tmp->next_;
    }
    std::cout << std::endl;
}

template<typename T>
inline size_t LinkList<T>::getSize() const {
    return size_;
}

#endif // _LINK_LIST_H_