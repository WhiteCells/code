#include "link_list.h"
#include <stdio.h>

#define TEST_FUNC_BEGIN printf("===> function: %s begin\n", __func__)
#define TEST_FUNC_END printf("<=== function: %s end\n\n", __func__)

void print(void *data) {
    printf("%d", *(int *)data);
}

bool compareValue(void *data1, void *data2) {
    return *(int *)data1 == *(int *)data2;
}

bool compareAddress(void *data1, void *data2) {
    return data1 == data2;
}

void test_insertHeadLinkList() {
    TEST_FUNC_BEGIN;
    LinkList *list = initLinkList();
    int a = 1, b = 2, c = 3;
    void *arr[] = {&a, &b, &c};
    createLinkList(list, arr, sizeof(arr) / sizeof(arr[0]));
    printLinkList(list, print); /* 1->2->3 */

    int val1 = 0;
    insertHeadLinkList(list, &val1);
    printLinkList(list, print); /* 0->1->2->3 */

    int val2 = -1;
    insertHeadLinkList(list, &val2);
    printLinkList(list, print); /* -1->0->1->2->3 */

    int val3 = -2;
    insertHeadLinkList(list, &val3);
    printLinkList(list, print); /* -2->-1->0->1->2->3 */

    destroyLinkList(list);
    TEST_FUNC_END;
}

void test_insertTailLinkList() {
    TEST_FUNC_BEGIN;
    LinkList *list = initLinkList();

    int vals[] = {1, 2, 3};
    int *arr[] = {&vals[0], &vals[1], &vals[2]};
    createLinkList(list, (void **)arr, sizeof(arr) / sizeof(arr[0]));
    printLinkList(list, print); /* 1->2->3 */

    int val4 = 4;
    insertTailLinkList(list, &val4);
    printLinkList(list, print); /* 1->2->3->4 */

    int val5 = 5;
    insertTailLinkList(list, &val5);
    printLinkList(list, print); /* 1->2->3->4->5 */

    int val6 = 6;
    insertTailLinkList(list, &val6);
    printLinkList(list, print); /* 1->2->3->4->5->6 */

    destroyLinkList(list);
    TEST_FUNC_END;
}

void test_insertPositionLinkList() {
    TEST_FUNC_BEGIN;
    LinkList *list = initLinkList();

    int vals[] = {1, 2, 3};
    int *arr[] = {&vals[0], &vals[1], &vals[2]};
    createLinkList(list, (void **)arr, sizeof(arr) / sizeof(arr[0]));
    printLinkList(list, print); /* 1->2->3 */

    int val1 = -1;
    insertPositionLinkList(list, 0, &val1);
    printLinkList(list, print); /* -1->1->2->3 */

    int val2 = 0;
    insertPositionLinkList(list, 1, &val2);
    printLinkList(list, print); /* -1->0->1->2->3 */

    int val3 = 4;
    insertPositionLinkList(list, 5, &val3);
    printLinkList(list, print); /* -1->0->1->2->3->4 */

    int val4 = 6;
    insertPositionLinkList(list, -111, &val4);
    printLinkList(list, print); /* -1->0->1->2->3->4->6 */

    int val5 = 5;
    insertPositionLinkList(list, 6, &val5);
    printLinkList(list, print); /* -1->0->1->2->3->4->5->6 */
    destroyLinkList(list);
    TEST_FUNC_END;
}

void test_deleteHeadLinkList() {
    TEST_FUNC_BEGIN;
    LinkList *list = initLinkList();

    int vals[] = {1, 2, 3};
    int *arr[] = {&vals[0], &vals[1], &vals[2]};
    createLinkList(list, (void **)arr, sizeof(arr) / sizeof(arr[0]));
    printLinkList(list, print); /* 1->2->3 */

    deleteHeadLinkList(list);
    printLinkList(list, print); /* 2->3 */

    deleteHeadLinkList(list);
    printLinkList(list, print); /* 3 */

    deleteHeadLinkList(list);
    printLinkList(list, print); /*  */

    deleteHeadLinkList(list);
    printLinkList(list, print); /*  */

    destroyLinkList(list);
    TEST_FUNC_END;
}

void test_deleteTailLinkList() {
    TEST_FUNC_BEGIN;
    LinkList *list = initLinkList();

    int vals[] = {1, 2, 3};
    int *arr[] = {&vals[0], &vals[1], &vals[2]};
    createLinkList(list, (void **)arr, sizeof(arr) / sizeof(arr[0]));
    printLinkList(list, print); /* 1->2->3 */

    deleteTailLinkList(list);
    printLinkList(list, print); /* 1->2 */

    deleteTailLinkList(list);
    printLinkList(list, print); /* 1 */

    deleteTailLinkList(list);
    printLinkList(list, print); /*  */

    deleteTailLinkList(list);
    printLinkList(list, print); /*  */

    destroyLinkList(list);
    TEST_FUNC_END;
}

void test_deleteValueLinkList() {
    TEST_FUNC_BEGIN;
    LinkList *list = initLinkList();

    int vals[] = {1, 2, 3};
    int *arr[] = {&vals[0], &vals[1], &vals[2]};
    createLinkList(list, (void **)arr, sizeof(arr) / sizeof(arr[0]));
    printLinkList(list, print); /* 1->2->3 */

    int delete_val = 2;
    deleteValueLinkList(list, &delete_val, compareValue);
    printLinkList(list, print); /* 1->3 */

    delete_val = 1;
    deleteValueLinkList(list, &delete_val, compareValue);
    printLinkList(list, print); /* 3 */

    destroyLinkList(list);
    TEST_FUNC_END;
}

void test_deletePositionLinkList() {
    TEST_FUNC_BEGIN;
    LinkList *list = initLinkList();

    int vals[] = {1, 2, 3};
    int *arr[] = {&vals[0], &vals[1], &vals[2]};
    createLinkList(list, (void **)arr, sizeof(arr) / sizeof(arr[0]));
    printLinkList(list, print); /* 1->2->3 */

    deletePositionLinkList(list, 0);
    printLinkList(list, print); /* 2->3 */

    deletePositionLinkList(list, 1);
    printLinkList(list, print); /* 2 */

    deletePositionLinkList(list, 1);
    printLinkList(list, print); /*  */

    destroyLinkList(list);
    TEST_FUNC_END;
}

void test_modifyValueLinkList() {
    TEST_FUNC_BEGIN;
    LinkList *list = initLinkList();

    int vals[] = {1, 2, 3};
    int *arr[] = {&vals[0], &vals[1], &vals[2]};
    createLinkList(list, (void **)arr, sizeof(arr) / sizeof(arr[0]));
    printLinkList(list, print); /* 1->2->3 */

    int modify_value1 = 2;
    int new_value1 = 20;
    modifyValueLinkList(list, &modify_value1, &new_value1, compareValue);
    printLinkList(list, print); /* 1->20->3 */

    int modify_value2 = 3;
    int new_value2 = 30;
    modifyValueLinkList(list, &modify_value2, &new_value2, compareValue);
    printLinkList(list, print); /* 1->20->30 */

    TEST_FUNC_END;
}

void test_modifyPositionLinkList() {
    TEST_FUNC_BEGIN;
    LinkList *list = initLinkList();

    int vals[] = {1, 2, 3};
    int *arr[] = {&vals[0], &vals[1], &vals[2]};
    createLinkList(list, (void **)arr, sizeof(arr) / sizeof(arr[0]));
    printLinkList(list, print); /* 1->2->3 */

    int modify_pos1 = 2;
    int new_value1 = 30;
    modifyPositionLinkList(list, modify_pos1, &new_value1);
    printLinkList(list, print); /* 1->2->30 */

    int modify_pos2 = 3;
    int new_value2 = 30;
    modifyPositionLinkList(list, modify_pos2, &new_value2);
    printLinkList(list, print); /* 1->2->30 */

    int modify_pos3 = 1;
    int new_value3 = 20;
    modifyPositionLinkList(list, modify_pos3, &new_value3);
    printLinkList(list, print); /* 1->20->30 */

    TEST_FUNC_END;
}

void test_findPositionLinkList() {
    TEST_FUNC_BEGIN;
    LinkList *list = initLinkList();

    int vals[] = {1, 2, 3};
    int *arr[] = {&vals[0], &vals[1], &vals[2]};
    createLinkList(list, (void **)arr, sizeof(arr) / sizeof(arr[0]));
    printLinkList(list, print); /* 1->2->3 */

    size_t pos = 1;
    ListNode *node = findPositionLinkList(list, pos);
    if (node) {
        printf("find pos %zu value : %d\n", pos, *(int *)node->data); /* find pos 1 value : 2 */
    }

    pos = 2;
    node = findPositionLinkList(list, pos);
    if (node) {
        printf("find pos %zu value : %d\n", pos, *(int *)node->data); /* find pos 2 value : 3 */
    }

    destroyLinkList(list);
    TEST_FUNC_END;
}

void test_findValueLinkList() {
    TEST_FUNC_BEGIN;
    LinkList *list = initLinkList();

    int vals[] = {1, 2, 3};
    int *arr[] = {&vals[0], &vals[1], &vals[2]};
    createLinkList(list, (void **)arr, sizeof(arr) / sizeof(arr[0]));
    printLinkList(list, print); /* 1->2->3 */

    int find_val1 = 2;
    size_t idx = findValueLinkList(list, &find_val1, compareValue);
    if (idx != -1) {
        printf("find value idx: %zu\n", idx); /* find value idx: 1 */
    }

    int find_val2 = 3;
    idx = findValueLinkList(list, &find_val2, compareValue);
    if (idx != -1) {
        printf("find value idx: %zu\n", idx); /* find value idx: 2 */
    }

    int find_val3 = 1;
    idx = findValueLinkList(list, &find_val3, compareValue);
    if (idx != -1) {
        printf("find value idx: %zu\n", idx); /* find value idx: 0 */
    }

    destroyLinkList(list);
    TEST_FUNC_END;
}

int main(int argc, char *argv[]) {

    test_insertHeadLinkList();

    test_insertTailLinkList();

    test_insertPositionLinkList();

    test_deleteHeadLinkList();

    test_deleteTailLinkList();

    test_deleteValueLinkList();

    test_deletePositionLinkList();

    test_modifyValueLinkList();

    test_modifyPositionLinkList();

    test_findPositionLinkList();

    test_findValueLinkList();

    return 0;
}