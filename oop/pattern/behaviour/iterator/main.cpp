#include "aggregate.h"
#include "iterator.h"
#include "vector_iterator.h"
#include <iostream>

int main(int argc, char *argv[]) {
    Aggregate<std::string> aggregate;

    aggregate.add("item1");
    aggregate.add("item2");
    aggregate.add("item3");

    Iterator<std::string> *iterator = aggregate.createIterator();
    while (iterator->hasNext()) {
        std::cout << iterator->next() << " ";
    }
    std::cout << std::endl;

    delete iterator;
    iterator = nullptr;
    return 0;
}