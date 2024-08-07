#include "D:\distake\Coding\head_file.h"

class MyStack {
public:
    MyStack() {

    }

    void push(int x) {
        inQueue.push(x);
    }

    int pop() {
        int count = inQueue.size() - 1;
        while (count--) {
            int frontval = inQueue.front();
            inQueue.push(frontval);
            inQueue.pop();
        }
        int val = inQueue.front();
        inQueue.pop();
        return val;
    }

    int top() {
        return inQueue.back();
    }

    bool empty() {
        return inQueue.empty();
    }
    queue<int> inQueue;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();s
 */

int main() {
    return 0;
}