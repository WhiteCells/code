#include "link_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

LinkList *initLinkList() {
    LinkList *list = (LinkList *)malloc(sizeof(LinkList));
    assert(list);
    list->head = NULL;
    list->size = 0;
    return list;
}

ListNode *initListNode(void *data, ListNode *next) {
    assert(data);
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    assert(node);
    node->data = data;
    node->next = next;
    return node;
}

void createLinkList(LinkList *list, void *arr[], int n) {
    assert(list);
    ListNode *cur = list->head;
    for (int i = 0; i < n; ++i) {
        if (!cur) {
            list->head = cur = initListNode(arr[i], NULL);
        } else {
            cur->next = initListNode(arr[i], NULL);
            cur = cur->next;
        }
    }
    list->size = n;
}

void insertHeadLinkList(LinkList *list, void *val) {
    assert(list);
    ListNode *new_node = initListNode(val, list->head);
    list->head = new_node;
    ++list->size;
}

void insertTailLinkList(LinkList *list, void *val) {
    assert(list);
    ListNode *cur = list->head;
    if (!cur) {
        list->head = initListNode(val, NULL);
        ++list->size;
        return;
    }
    while (cur && cur->next) {
        cur = cur->next;
    }
    cur->next = initListNode(val, NULL);
    ++list->size;
}

void insertPositionLinkList(LinkList *list, size_t pos, void *data) {
    assert(list);
    if (0 == pos) {
        insertHeadLinkList(list, data);
        return;
    }
    if (pos > list->size) {
        pos = list->size;
    }
    ListNode *cur = list->head;
    for (size_t i = 0; i + 1 < pos; ++i) {
        cur = cur->next;
    }
    ListNode *next_node = cur->next;
    cur->next = initListNode(data, next_node);
    ++list->size;
}

void deleteHeadLinkList(LinkList *list) {
    assert(list);
    ListNode *cur = list->head;
    if (!cur) {
        return;
    }
    ListNode *tmp = cur->next;
    free(cur);
    list->head = tmp;
    --list->size;
}

void deleteTailLinkList(LinkList *list) {
    assert(list);
    ListNode *cur = list->head;
    if (!cur) {
        return;
    }
    if (!cur->next) {
        free(cur);
        list->head = NULL;
        --list->size;
        return;
    }
    while (cur && cur->next && cur->next->next) {
        cur = cur->next;
    }
    ListNode *delete_node = cur->next;
    cur->next = NULL;
    free(delete_node);
    --list->size;
}

bool deleteValueLinkList(LinkList *list, void *data, COMPARE_DATA compare) {
    assert(list);
    ListNode *cur = list->head;
    if (compare(cur->data, data)) {
        deleteHeadLinkList(list);
        return true;
    }
    while (cur && cur->next) {
        if (compare(cur->next->data, data)) {
            ListNode *delete_node = cur->next;
            cur->next = delete_node->next;
            free(delete_node);
            --list->size;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

bool deletePositionLinkList(LinkList *list, size_t pos) {
    assert(list);
    if (pos >= list->size) {
        pos = list->size - 1;
    }
    if (0 == pos) {
        deleteHeadLinkList(list);
        return true;
    }
    ListNode *cur = list->head;
    for (size_t i = 0; i + 1 < pos; ++i) {
        cur = cur->next;
    }
    ListNode *delete_node = cur->next;
    cur->next = delete_node->next;
    free(delete_node);
    --list->size;
    return true;
}

bool modifyValueLinkList(LinkList *list, void *find_data, void *new_data, COMPARE_DATA compare) {
    assert(list);
    assert(find_data);
    // size_t pos = findValueLinkList(list, find_data, compare);
    // if (pos != -1) {
    //     ListNode *find_node = findPositionLinkList(list, pos);
    //     find_node->data = new_data;
    //     return true;
    // }
    ListNode *cur = list->head;
    while (cur) {
        if (compare(cur->data, find_data)) {
            cur->data = new_data;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

bool modifyPositionLinkList(LinkList *list, size_t pos, void *new_data) {
    assert(list);
    if (pos >= list->size) {
        return false;
    }
    ListNode *find_node = findPositionLinkList(list, pos);
    find_node->data = new_data;
    return true;
}

ListNode *findPositionLinkList(LinkList *list, size_t pos) {
    assert(list);
    if (pos >= list->size) {
        return NULL;
    }
    ListNode *cur = list->head;
    for (size_t i = 0; i < pos; ++i) {
        cur = cur->next;
    }
    return cur;
}

size_t findValueLinkList(LinkList *list, void *data, COMPARE_DATA compare) {
    assert(list);
    size_t pos = -1;
    ListNode *cur = list->head;
    for (size_t i = 0; i < list->size; ++i) {
        if (compare(cur->data, data)) {
            return i;
        }
        cur = cur->next;
    }
    return pos;
}

size_t getLinkListSize(LinkList *list) {
    return list->size;
}

void destroyLinkList(LinkList *list) {
    if (list) {
        ListNode *cur = list->head;
        while (cur) {
            ListNode *tmp = cur->next;
            free(cur);
            cur = tmp;
        }
        free(list);
    }
}

void printLinkList(LinkList *list, PRINT_DATA_FUNC_PTR print) {
    assert(list);
    int n = 0;
    ListNode *tmp = list->head;
    while (tmp) {
        // printf("%d", *(int *)tmp->data);
        print(tmp->data);
        if (++n < list->size) {
            printf("->");
        }
        tmp = tmp->next;
    }
    printf("\n");
}