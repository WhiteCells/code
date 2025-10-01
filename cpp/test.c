#include <stdio.h>
#include <string.h>

int main()
{
    double a = 1.111111111111111111111111111111111111111111111111111111111111;
    printf("%.50f\n", a);
    const char *str = "1.11111111111111116045435665000695735216140747070312";
    int l = strlen(str);
    printf("%d", l);
}