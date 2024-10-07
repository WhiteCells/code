#ifndef _VECTOR_ITERATOR_H_
#define _VECTOR_ITERATOR_H_

#include "iterator.h"
#include <cstddef>

template<typename T>
class VectorIterator : public Iterator<T> {
public:
    VectorIterator(const std::vector<T> &vec);
    virtual T next() override;
    virtual bool hasNext() const override;

private:
    const std::vector<T> &vec_;
    size_t index_;
};

template<typename T>
VectorIterator<T>::VectorIterator(const std::vector<T> &vec)
    : vec_(vec), index_(0) {

}

template<typename T>
T VectorIterator<T>::next() {
    return vec_[index_++];
}

template<typename T>
bool VectorIterator<T>::hasNext() const {
    return index_ < vec_.size();
}

#endif // _VECTOR_ITERATOR_H_