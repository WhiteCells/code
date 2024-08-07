#include <stdio.h>
#include <stdlib.h>

typedef struct SeqList {
    int *data;
    int size;
    int capacity;
} SeqList;

// [1] [2] [3] [4] [ ]
// capacity = 5
// size = 4
void initSeqList(SeqList *list, int capacity) {
    list->data = (int *)malloc(sizeof(int) * capacity);
    list->capacity = capacity;
    list->size = 0;
}

void test_initSeqList() {
    SeqList *seqlist = (SeqList *)malloc(sizeof(SeqList));
    initSeqList(seqlist, 5);

}

// insert

// delete

int main(int argc, char *argv[]) {
    SeqList l;
    int size3 = sizeof(SeqList);
    return 0;
}