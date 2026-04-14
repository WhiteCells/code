#include "acc.h"
#include "call.h"

int main(int argc, char *argv[])
{
    Acc acc;
    Call call(acc);
    call.hangup();
    return 0;
}