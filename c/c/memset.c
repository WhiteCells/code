#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n = 5;
    int *arr = (int *)malloc(sizeof(int) * n);

    for (int i = 0; (i == n ? printf("\n") : printf("%d ", *(arr + i))) && i < n; ++i);

    memset(arr, 0, sizeof(int) * n);

    for (int i = 0; (i == n ? printf("\n") : printf("%d ", *(arr + i))) && i < n; ++i);

    free(arr);
    return 0;
}