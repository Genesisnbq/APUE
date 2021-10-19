#include "apue.h"

int main(void)
{
    printf("hello world from prcess ID %lld\n", (long long)getpid());
    return 0;
}