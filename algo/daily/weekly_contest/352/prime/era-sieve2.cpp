#include "../../../head_file.h"

// 运用埃氏筛法，计算 [0, N) 的质数表，prime_table，1 表示被筛除

const int N = 1e7;

// bitset<N> prime_table;
int prime_table[N] = {}; // 初始化为 0

int cnt = 0;

inline void EraPrime() {
    for (int i = 2; i <= N / i; ++i) {
        if (!prime_table[i]) {
            for (int j = i * i; j <= N; j += i) {
                prime_table[j] = 1;
            }
        }
    }

    for (int i = 2; i <= N; ++i) { // 统计 [2, N)
        if (!prime_table[i]) {
            ++cnt;
        }
    }
}

int main() {
    double s = clock();

    EraPrime();

    double e = clock();
    printf("%d\n%.1lfms", cnt, e - s);
    return 0;
}