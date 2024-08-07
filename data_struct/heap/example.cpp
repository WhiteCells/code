#include "heap.h"

#include <iostream>

template<typename T>
void execHeap(Heap<T> &h) {
    while (!h.empty()) {
        std::cout << h.top() << std::endl;
        h.pop();
    }
}

int main(int argc, char *argv[]) {
    Heap<int> h;
    h.push(1);
    h.push(2);
    h.push(4);
    h.push(3);
    h.push(5);
    execHeap(h);

    std::cout << "---" << std::endl;

    Heap<int> h2(false);
    h2.push(2);
    h2.push(3);
    h2.push(-1);
    h2.push(-1);
    h2.push(5);
    h2.push(5);
    h2.push(5);
    h2.push(1);
    h2.push(-1);
    h2.push(0);
    execHeap(h2);

    return 0;
}