#include "link_list.h"
#include <list>

int main(int argc, char *argv[]) {
    LinkList<int> list;

    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(2);
    list.insertBack(2);
    list.insertBack(3);

    list.insertFront(0);
    list.insertFront(-1);
    list.insertFront(-2);

    list.deleteBack();
    list.deleteFront();
    list.deleteFront();

    list.deleteByVal(2);

    list.print();
    list.print();

    LinkList<int> list2({1, 1, 1, 3, 2, 2});

    list2.print();
    // list2.deleteByVal(1);
    list2.deleteByIdx(3);
    list2.print();

    LinkList<int> list3 = {1, 1, 1, 3};
    list3.print();

    return 0;
}