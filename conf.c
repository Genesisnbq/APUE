#include <stdio.h> 

int main() {
    int sum = 0, n = 100;
    for (int i = 0; i < n; i++) {
        sum += i;
    }
    printf("sum = %d\n", sum);
    printf("Hello world!\n");
    return 0;
}