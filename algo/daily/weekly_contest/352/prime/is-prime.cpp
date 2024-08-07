#include "../../../head_file.h"

// 朴素

const int N = 1e7;
int cnt = 0;

bool IsPrime(int x) {

    // 18919.0ms
    // for (int i = 2; i <= sqrt(x); ++i) { // sqrt() 运算慢

    // 3692.0ms
    // for (int i = 2; i * i <= x; ++i) { // 溢出

    // 5244.0ms
    for (int i = 2; i <= x / i; ++i) { // 除法运算慢，但解决溢出
        if (0 == x % i) {
            return false;
        }
    }

    return true;
}

void CntPrime() {
    for (int i = 2; i <= N; ++i) { // 除 2 之外只有奇数才可能是素数
        if (IsPrime(i)) {
            ++cnt;
        }
    }
}

int main() {
    double s = clock();

    CntPrime();

    double e = clock();
    printf("%d\n%.1lfms", cnt, e - s);
    return 0;
}