#include "D:\distake\Coding\head_file.h"

class MyQueue {
public:
    MyQueue() {}

    void push(int x) {
        s1.push(x);
    }
    // 返回头部，队列头部移除
    int pop() {
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
        int val = s2.top();
        s2.pop();
        while (!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }
        return val;
    }
    // 返回队列头部
    int peek() {
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
        int val = s2.top();
        while (!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }
        return val;
    }

    bool empty() {
        return s1.empty();
    }
    // stack<int, vector<int>> s1;
    // stack<int, vector<int>> s2;
    stack<int> s1;
    stack<int> s2;
};

class MyQueue2 {
public:
    MyQueue2() {}

    void push(int x) {
        inStack.push(x);
    }
    // 返回头部，队列头部移除
    int pop() {
        if (outStack.empty()) {
            while (!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
        }
        int val = outStack.top();
        outStack.pop();
        return val;
    }
    // 返回队列头部
    int peek() {
        int val = this->pop();
        outStack.push(val); // 删除数据再入栈，peek不需要删除
        return val;
    }
    // 判断栈是否为空
    bool empty() {
        return inStack.empty() && outStack.empty();
    }
    stack<int> inStack;
    stack<int> outStack;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

int main() {

    return 0;
}