#ifndef _HEAP2_H_
#define _HEAP2_H_

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <cassert>

namespace ds {

template<typename T>
class Heap {
public:
    Heap(bool is_min_heap = true);
    Heap(const std::vector<T> &nums, bool is_min_heap = true);
    ~Heap();

    void push(const T &data);
    void pop();
    T top() const;

    size_t size() const;
    bool empty() const;

    void make(const std::vector<T> &nums);

private:
    void up(size_t idx);
    void down(size_t idx);

    size_t getParentIdx(size_t idx) const;
    size_t getLeftChildIdx(size_t idx) const;
    size_t getRightChildIdx(size_t idx) const;

    void swap(size_t idx1, size_t idx2);
    bool compare(size_t parent_idx, size_t idx) const;

    std::vector<T> heap_;
    bool is_min_heap_;
};

template<typename T>
inline Heap<T>::Heap(bool is_min_heap) :
    is_min_heap_(is_min_heap) {

}

template<typename T>
Heap<T>::Heap(const std::vector<T> &nums, bool is_min_heap) :
    heap_(nums),
    is_min_heap_(is_min_heap) {
    for (size_t i = getParentIdx(size() - 1); i >= 0; --i) {
        down(i);
    }
}

template<typename T>
inline Heap<T>::~Heap() {

}

template<typename T>
inline void Heap<T>::push(const T &data) {
    heap_.push_back(data);
    up(size() - 1);
}

template<typename T>
inline void Heap<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Heap is empty");
    }
    heap_[0] = heap_.back();
    heap_.pop_back();
    down(0);
}

template<typename T>
inline T Heap<T>::top() const {
    if (empty()) {
        throw std::runtime_error("Heap is empty");
    }
    return heap_[0];
}

template<typename T>
inline size_t Heap<T>::size() const {
    return heap_.size();
}

template<typename T>
inline bool Heap<T>::empty() const {
    return heap_.empty();
}

template<typename T>
inline void Heap<T>::make(const std::vector<T> &nums) {
    heap_ = nums;
    for (size_t i = getParentIdx(size() - 1); i >= 0; --i) {
        down(i);
    }
}

template<typename T>
inline void Heap<T>::up(size_t idx) {
    size_t parent_idx = getParentIdx(idx);
    if (idx > 0 && compare(parent_idx, idx)) {
        swap(parent_idx, idx);
        up(parent_idx);
    }
}

template<typename T>
inline void Heap<T>::down(size_t idx) {
    size_t left_child_idx = getLeftChildIdx(idx);
    size_t right_child_idx = getRightChildIdx(idx);
    size_t curr_idx = idx;

    if (left_child_idx < size() && compare(curr_idx, left_child_idx)) {
        curr_idx = left_child_idx;
    }
    if (right_child_idx < size() && compare(curr_idx, right_child_idx)) {
        curr_idx = right_child_idx;
    }

    if (curr_idx != idx) {
        swap(curr_idx, idx);
        down(curr_idx);
    }
}

template<typename T>
inline size_t Heap<T>::getParentIdx(size_t idx) const {
    return (idx - 1) / 2;
}

template<typename T>
inline size_t Heap<T>::getLeftChildIdx(size_t idx) const {
    return (idx * 2) + 1;
}

template<typename T>
inline size_t Heap<T>::getRightChildIdx(size_t idx) const {
    return (idx * 2) + 2;
}

template<typename T>
inline void Heap<T>::swap(size_t idx1, size_t idx2) {
    std::swap(heap_[idx1], heap_[idx2]);
}

template<typename T>
inline bool Heap<T>::compare(size_t parent_idx, size_t idx) const {
    assert(parent_idx < idx);

    if (is_min_heap_) {
        return heap_[parent_idx] > heap_[idx];
    }
    return heap_[parent_idx] < heap_[idx];
}

} // ds

#endif // _HEAP2_H_