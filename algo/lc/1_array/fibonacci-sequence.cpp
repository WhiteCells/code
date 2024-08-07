#include "../../head_file.h"

// 兔子数列-递归方式求解
long long Fibonacci1(int num) {
    if (num == 1 || num == 2) return 1;
    return Fibonacci1(num - 1) + Fibonacci1(num - 2);
}

// 兔子数列-数组的方式求解
long long Fibonacci2(int num) {
    if (num == 1 || num == 2) return 1;
    if (num == 3) return 2;
    long long rabbit_arr[3] = { 1, 1, 2 };
    for (int i = 0, index = 0; i < (num - 1) / 3; ++i) {
        rabbit_arr[0] = rabbit_arr[1] + rabbit_arr[2];
        rabbit_arr[1] = rabbit_arr[0] + rabbit_arr[2];
        rabbit_arr[2] = rabbit_arr[0] + rabbit_arr[1];
    }
    return rabbit_arr[(num - 1) % 3];
}

// 兔子数列-简化版
long long Fibonacci3(int num) {
    if (num == 1 || num == 2) return 1;
    if (num == 3) return 2;
    long long a = 1, b = 2, c = 3;
    for (int i = 3; i < num; ++i) {
        c = a + b;
        // 修改 a 和 b 的值
        a = b;
        b = c;
    }
    return c;
}

// 兔子数列-简化版优化
long long Fibonacci4(int num) {
    if (num == 1 || num == 2) return 1;
    if (num == 2) return 2;
    long long a = 1, b = 1, c = 2;
    for (int i = 0; i < num - 3; ++i) {
        a = b;
        b = c;
        c = a + b;
    }
    return c;
}

int main() {
    int num = 0;
    cin >> num;
    cout << Fibonacci4(num);
    return 0;
}