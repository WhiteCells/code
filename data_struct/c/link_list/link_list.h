#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

#include <stddef.h>
#include <stdbool.h>

typedef struct ListNode {
    void *data;
    struct ListNode *next;
} ListNode;

typedef struct LinkList {
    int size;
    ListNode *head;
} LinkList;

typedef void (*PRINT_DATA_FUNC_PTR)(void *);
typedef bool (*COMPARE_DATA)(void *, void *);

extern LinkList *initLinkList();

extern ListNode *initListNode(void *data, ListNode *next);

extern void createLinkList(LinkList *list, void *arr[], int n);

extern void insertHeadLinkList(LinkList *list, void *val);

extern void insertTailLinkList(LinkList *list, void *val);

extern void insertPositionLinkList(LinkList *list, size_t pos, void *data);

extern void deleteHeadLinkList(LinkList *list);

extern void deleteTailLinkList(LinkList *list);

extern bool deleteValueLinkList(LinkList *list, void *data, COMPARE_DATA compare);

extern bool deletePositionLinkList(LinkList *list, size_t pos);

extern bool modifyValueLinkList(LinkList *list, void *find_data, void *new_data, COMPARE_DATA compare);

extern bool modifyPositionLinkList(LinkList *list, size_t pos, void *new_data);

extern ListNode *findPositionLinkList(LinkList *list, size_t pos);

extern size_t findValueLinkList(LinkList *list, void *data, COMPARE_DATA compare);

extern size_t getLinkListSize(LinkList *list);

extern void destroyLinkList(LinkList *list);

extern void printLinkList(LinkList *list, PRINT_DATA_FUNC_PTR print);

#endif // _LINK_LIST_H_