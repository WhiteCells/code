#include <stdio.h>

int main() {
    unsigned g = 1u;

    int a0 = 10;
    int a1 = 0b10;
    int a2 = 010;
    int a3 = 0x10;
    printf("%d\n", a0);
    printf("%d\n", a1);
    printf("%d\n", a2);
    printf("%d\n", a3);

    float b2 = 10.0f;
    float b3 = 10.0F;

    double c = 10.0;

    long d1 = 10l;

    long double d2 = 10.0l;
    long double d3 = 10.0L;

    long long e1 = 10ll;
    long long e2 = 10LL;

    unsigned long f1 = 20ul;
    unsigned long f2 = 20UL;

    unsigned long long h1 = 20ull;
    unsigned long long h2 = 20ULL;
    return 0;
}