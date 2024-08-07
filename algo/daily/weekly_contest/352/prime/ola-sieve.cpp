#include "../../../head_file.h"

// 运用欧拉筛法（线性筛），计算 [0, N) 的质数表，prime_table，1 表示被筛除

const int N = 1e8;

// 216ms
// bitset<N> prime_table;

// 100ms
int prime_table[N] = {};

int prime[N], idx = 0, cnt = 0;

inline void OlaPrime() {
    for (int i = 2; i <= N; ++i) {
        if (!prime_table[i]) {
            prime[++idx] = i;
            ++cnt; // 顺带统计个数
        }
        for (int j = 1; prime[j] * i <= N; ++j) {
            prime_table[prime[j] * i] = 1;
            if (0 == i % prime[j]) {
                break;
            }
        }
    }
}

int main() {
    double s = clock();

    OlaPrime();

    double e = clock();
    printf("%d\n%lfms", cnt, e - s);
    return 0;
}