#ifndef _HEAP_H_
#define _HEAP_H_

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cstddef>

template<typename T>
class Heap {
public:
    Heap(bool is_min_heap = true);
    ~Heap();

    void push(const T &data);
    void pop();
    T top() const;

    bool empty() const;
    size_t size() const;

private:
    void up(size_t idx);
    void down(size_t idx);

    size_t getParentIndex(size_t idx) const;
    size_t getLeftChildIndex(size_t idx) const;
    size_t getRightChildIndex(size_t idx) const;
    bool compare(const T &father, const T &son) const;

    std::vector<T> heap_;
    bool is_min_heap_;
};

template<class T>
inline Heap<T>::Heap(bool is_min_heap) :
    is_min_heap_(is_min_heap) {

}

template<class T>
inline Heap<T>::~Heap() {

}

template<class T>
inline void Heap<T>::push(const T &data) {
    heap_.push_back(data);
    up(size() - 1);
}

template<class T>
inline void Heap<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Heap is empty");
    }
    heap_[0] = heap_.back();
    heap_.pop_back();
    down(0);
}

template<class T>
inline T Heap<T>::top() const {
    if (empty()) {
        throw std::runtime_error("Heap is empty");
    }
    return heap_[0];
}

template<class T>
inline bool Heap<T>::empty() const {
    return heap_.empty();
}

template<class T>
inline size_t Heap<T>::size() const {
    return heap_.size();
}

template<class T>
inline void Heap<T>::up(size_t idx) {
    int parent_idx = getParentIndex(idx);
    if (idx > 0 && compare(heap_[parent_idx], heap_[idx])) {
        std::swap(heap_[idx], heap_[parent_idx]);
        up(parent_idx);
    }
}

template<class T>
inline void Heap<T>::down(size_t idx) {
    size_t left_child_idx = getLeftChildIndex(idx);
    size_t right_child_idx = getRightChildIndex(idx);
    size_t curr_idx = idx;

    if (left_child_idx < heap_.size()
        && compare(heap_[curr_idx], heap_[left_child_idx])) {
        curr_idx = left_child_idx;
    }
    if (right_child_idx < heap_.size()
        && compare(heap_[curr_idx], heap_[right_child_idx])) {
        curr_idx = right_child_idx;
    }

    if (curr_idx != idx) {
        std::swap(heap_[curr_idx], heap_[idx]);
        down(curr_idx);
    }
}

template<class T>
inline size_t Heap<T>::getParentIndex(size_t idx) const {
    return (idx - 1) / 2;
}

template<class T>
inline size_t Heap<T>::getLeftChildIndex(size_t idx) const {
    return (idx * 2) + 1;
}

template<class T>
inline size_t Heap<T>::getRightChildIndex(size_t idx) const {
    return (idx * 2) + 2;
}

template<class T>
inline bool Heap<T>::compare(const T &father, const T &son) const {
    if (is_min_heap_) {
        // when the father is greater than the son，
        // it does not satisfy the min_heap condition
        // and needs to be exchanged so it returns true
        return father > son;
    }
    return father < son;
}

#endif // _HEAP_H_