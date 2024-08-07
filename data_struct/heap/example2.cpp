#include "heap2.h"

#include <iostream>

template<typename T>
void printHeap(ds::Heap<T> &heap) {
    while (!heap.empty()) {
        std::cout << "current heap top: " << heap.top() << std::endl;
        // std::cout << "current heap size: " << heap.size() << std::endl << std::endl;
        heap.pop();
    }
    std::cout << "---" << std::endl;
}

int main(int argc, char *argv[]) {
    ds::Heap<int> heap;
    heap.push(1);
    heap.push(3);
    heap.push(2);
    heap.push(5);
    heap.push(4);
    heap.push(0);
    printHeap(heap);

    ds::Heap<int> heap2(false);
    heap2.push(1);
    heap2.push(-2);
    heap2.push(0);
    heap2.push(3);
    heap2.push(2);
    heap2.push(-1);
    printHeap(heap2);

    ds::Heap<int> heap3({1, 2, -2, -1, 0});
    printHeap(heap3);

    return 0;
}