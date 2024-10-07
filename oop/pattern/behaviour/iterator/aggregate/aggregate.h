#ifndef _AGGREGATE_H_
#define _AGGREGATE_H_

#include "vector_iterator.h"

template<typename T>
class Aggregate {
public:
    Aggregate();
    void add(T item);
    Iterator<T> *createIterator();

private:
    std::vector<T> items_;
};

template<typename T>
Aggregate<T>::Aggregate() {

}

template<typename T>
void Aggregate<T>::add(T item) {
    items_.push_back(item);
}

template<typename T>
Iterator<T> *Aggregate<T>::createIterator() {
    return new VectorIterator<T>(items_);
}

#endif // _AGGREGATE_H_