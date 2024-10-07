#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include <vector>

template<typename T>
class Iterator {
public:
    virtual ~Iterator() = 0;
    virtual T next() = 0;
    virtual bool hasNext() const = 0;
};

template<typename T>
Iterator<T>::~Iterator() {}

#endif // _ITERATOR_H_