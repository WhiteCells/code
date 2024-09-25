#include <stdio.h>
#include <stdlib.h>

// 传引用：形参的改变可以影响实参
void foo1(int &a)
{
    a = 20;
}

// 传值：形参的改变不会影响实参
void foo2(int a)
{
    a = 20;
}

void foo3(int &a, int &b, int &c)
{
    a = 1;
    b = 2;
    c = 3;
}

void foo4()
{
    return;
}

int foo5()
{
    return 1;
}

void foo6(int arr[])
{
}

void foo7(int *arr)
{
    arr = NULL;
}

void test()
{
    int a = 1;
}

void foo9(int *arr, int n)
{
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void foo10(int *arr)
{
    // 指针占 8 个字节
    int n = sizeof(arr) / sizeof(arr[0]); // 2
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n"); 
}

void foo11(int arr[])
{
    // 指针占 8 个字节
    int n = sizeof(arr) / sizeof(arr[0]); // 2
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void foo8()
{
    // int arr[] = {1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
    int arr[] = {1, 2, 3, 1};

    // sizeof() 计算出类型所占的内存大小（字节）
    int n = sizeof(arr) / sizeof(arr[0]); // 4
    foo9(arr, n);
    foo10(arr);
    foo11(arr);

    //           0  1  2
    // arr[0] 访问下标为 0 的元素 = 1
    int a = arr[0];
    int b = arr[1];
    int c = arr[2];
    // int d = arr[3];

    // printf("%d\n", *(arr + 0));
    // printf("%d\n", *(arr + 1));
    // printf("%d\n", *(arr + 2));
}

int *foo12(int &n)
{
    n = 10;
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) {
        *(arr + i) = i;
    }
    return arr;
}

void foo13()
{
    int n;
    int *res = foo12(n);
    for (int i = 0; i < n; ++i) {
        printf("%d\n", *(res + i));
    }
    free(res);
}

int main(int argc, char *argv[])
{
    foo13();
    //     int a = 10;
    //     foo1(a);
    //     printf("%d\n", a);

    //     // foo2(a);
    //     // printf("%d\n", a); // 10

    //     // printf("%d\n", foo3());

    //     int x, y, z;
    //     foo3(x, y, z);

    //     printf("%d %d %d\n", x, y, z);

    //     int qehqwuiehqwuieb = a;
    //     qehqwuiehqwuieb = 1000000000;

    //     printf("%d\n", a);

    //     int arr[] = {1, 2, 3};
    //     foo7(arr);

    //     printf("arr[0]: %d\n", arr[0]);

    // foo8();

    // int c = 10101;

    // printf("%d\n", c);

    return 0;
}