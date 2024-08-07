#include "../../head_file.h"

class MyLinkedList {
public:
    MyLinkedList() {
        _head = new LinkedList(0);
        _size = 0;
    }

    int get(int index) {
        if (index < 0 || index >= this->_size) {
            return -1;
        }
        LinkedList* cur_node = _head->next;
        for (int i = 0; i < index; ++i) {
            cur_node = cur_node->next;
        }
        return cur_node->val;
    }
    // 头插
    void addAtHead(int val) {
        LinkedList* new_node = new LinkedList(val);
        new_node->next = _head->next;
        _head->next = new_node;
        ++_size;
    }
    // 尾插
    void addAtTail(int val) {
        LinkedList* new_node = new LinkedList(val);
        LinkedList* cur_node = _head; // 记录 _head，不用单独考虑 _head->next == nullptr 情况
        while (cur_node->next != nullptr) {
            cur_node = cur_node->next;
        }
        cur_node->next = new_node;
        ++_size;
    }
    // 下标插入
    void addAtIndex(int index, int val) {
        if (index < 0 || index > this->_size) { // index > _size，适用 index == _size，就是尾插的形式
            return;
        }
        LinkedList* new_node = new LinkedList(val);
        LinkedList* cur_node = _head; // 记录 _head，适用 index == 0 时
        for (int i = 0; i < index; ++i) {
            cur_node = cur_node->next;
        }
        new_node->next = cur_node->next;
        cur_node->next = new_node;
        ++_size;
    }
    // 下标删除
    void deleteAtIndex(int index) {
        if (index < 0 || index >= this->_size) {
            return;
        }
        LinkedList* cur_node = _head; // 记录 _head，适用 index == 0 时
        for (int i = 0; i < index; ++i) {
            cur_node = cur_node->next;
        }
        LinkedList* temp = cur_node->next;
        cur_node->next = temp->next;
        delete temp;
        --_size;
    }
    // 打印
    void printLinkedList() {
        if (_head->next == nullptr) return;
        LinkedList* cur_node = _head->next;
        while (cur_node != nullptr) {
            cout << cur_node->val << " ";
            cur_node = cur_node->next;
        }
    }
private:
    struct LinkedList {
        int val;
        LinkedList* next;
        LinkedList(int val): val(val), next(nullptr) {}
    };
    LinkedList* _head;
    int _size;
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */


int main() {
    MyLinkedList list;
    // list.addAtHead(1);
    // list.addAtHead(2);
    // list.addAtHead(3);
    // list.addAtHead(4);
    list.addAtTail(1);
    list.addAtTail(2);
    list.addAtTail(3);
    list.addAtTail(4);
    // cout << list.get(1) << endl;
    // list.deleteAtIndex(1);
    list.addAtIndex(4, 5);
    // list.deleteAtIndex(3);
    list.printLinkedList();
    return 0;
}