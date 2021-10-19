#include <stdio.h> // for printf
#include <math.h>

int main() {
    long long a = ~(1 << 31);

    long long b = (long long)pow(2, 31) - 1;
    printf("%lld %lld\n", a, b);
}   

