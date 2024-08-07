#include <iostream>
#include <bitset>
#include <ctime>

using namespace std;

// 11
// 2 3 4 5 6 7 8 9 10 11
// a * b == 11
// a 或 b 必有一个 <= sqrt(1)，所以只用判断 [2, sqrt(11)] 能不能整除 11 即可判断 11 是否为质数

inline bool isprime1(int x) {

    // 98117.000000ms
    // for (int i = 2; i < x; ++i) {
    //     if (0 == x % i) {
    //         return false;
    //     }
    // }

    // 循环范围、步长、跳出条件

    // 734ms
    // for (int i = 2; i <= sqrt(x); ++i) { // sqrt() 计算较慢
    //     if (0 == x % i) {
    //         return false;
    //     }
    // }

    // 126ms
    // for (int i = 2; i * i <= x; ++i) { // i * i 可能会溢出
    //     if (0 == x % i) {
    //         return false;
    //     }
    // }

    // 203ms
    // for (int i = 2; i <= x / i; ++i) { // 除法慢一些，但可防止溢出
    //     if (0 == x % i) {
    //         return false;
    //     }
    // }

    return true;
}

// 一个合数，一定存在非 1 非本身质因子
// 4 == 2 * 2
// 把 2 的倍数全部筛掉，

const int maxn = 1e7;

// bool prime[maxn] = {};
bitset<maxn> prime; // 默认全部为零，0 为素数，1 合数（被筛除）

int main() {
    int N = 1e7, cnt = 0;
    double s = clock();

    // prime1 判断是否为质数
    // for (int i = 2; i <= N; ++i) { // 78498
    //     if (isprime1(i)) {
    //         ++cnt;
    //     }
    // }

    // prime2 筛法
    // 75ms
    // for (int i = 2; i <= N / i; ++i) { // 筛到 sqrt(N)
    //     if (isprime2(i)) {
    //         for (int j = i * 2; j <= N; j += i) {
    //             prime[j] = 1; // 标记进行筛除
    //         }
    //     }
    // }
    // for (int i = 2; i <= N; ++i) {
    //     if (!prime[i]) {
    //         ++cnt;
    //     }
    // }

    // prime3 筛法优化，不进行素数判断，直接进行筛选
    // 类埃氏筛法
    // 31ms
    // for (int i = 2; i <= N / i; ++i) {
    //     if (!prime[i]) {
    //         for (int j = i * 2; j <= N; j += i) {
    //             prime[j] = 1;
    //         }
    //     }
    // }
    // for (int i = 2; i <= N; ++i) {
    //     if (!prime[i]) {
    //         ++cnt;
    //     }
    // }

    // 埃氏筛法
    // 29ms
    for (int i = 2; i <= N / i; ++i) {
        if (!prime[i]) {
            for (int j = i * i; j <= N; j += i) {
                prime[j] = 1;
            }
        }
    }
    for (int i = 2; i <= N; ++i) {
        if (!prime[i]) {
            ++cnt;
        }
    }

    double e = clock();
    printf("%d\ntime = %lfms", cnt, e - s);
    return 0;
}