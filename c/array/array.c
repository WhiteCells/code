#include <stdio.h>
#include <string.h>

// [row][col]
int arr[2][5] = {
    {1, 2, 3, 4, 5},
    {1, 2, 3, 4, 5},
};

int arr2[][5] = {
    {1, 2, 3, 4, 5},
    {1, 2, 3, 4, 5},
};

int arr3[][2][5] = {
    {
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
    }, {
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
    }, {
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
    }
};

/**
 * 函数传入字符串长度参数的原因：
 * 1. 影响性能，strlen 可以计算字符串的长度，但是其计算的方式是遍历整个字符串，直至 `\0`
 * 2. 需要处理字符串的一部分而不是全部时，传递字符串长度
 * 3. 字符串不以 `\0` 结尾时
 * 4. 安全考虑，防止溢出缓冲区
 */
void test_strlen(const char *str1, char str2[]) {
    int len1 = strlen(str1);
    printf("parameter str1 len: %d\n", len1);

    int len2 = strlen(str2);
    printf("parameter str2 len: %d\n", len2);
    printf("------------------\n");
    printf("arr -> ptr str2 %zu\n", sizeof(str2));
    printf("------------------\n\n");
}

void test_parameter() {
    char arr1[] = "123"; // 字符串字面量会自动添加一个空字符 `\0`
    char arr2[] = {'1', '2', '3'}; // 数组没有空字符 \0 终止符
    char arr3[] = {'1', '2', '3', '\0'};
    test_strlen("123", arr1);
    test_strlen("123", arr2); // strlen(arr2) ub
    test_strlen("123", arr3);

    printf("sizeof(arr1) %zu\n", sizeof(arr1));
    printf("sizeof(arr2) %zu\n", sizeof(arr2));
    printf("sizeof(arr3) %zu\n", sizeof(arr3));
    printf("sizeof(arr1[0]) %zu\n", sizeof(arr1[0]));
    printf("sizeof(arr2[0]) %zu\n", sizeof(arr2[0]));
    printf("sizeof(arr3[0]) %zu\n", sizeof(arr3[0]));
}

void testPtrAndArr() {
    const char *argv[4];
    int argv_len[4];
    argv[0] = "hset";
    argv_len[0] = strlen(argv[0]);
    printf("%d\n", argv_len[0]);

    char str[] = "hset";
    int len = sizeof(str) / sizeof(str[0]);
    int str_len = strlen(str);
    printf("%d\n", len);
    printf("%d\n", str_len);
}

int main() {
    test_parameter();
    if ('\0' == NULL) {
        printf("'\\0' == NULL\n");
    }
    return 0;
}