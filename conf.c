#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    srand(time(NULL));

    while (1) {
        printf("%d\n", (rand() % 7 + 1) * (rand() % 7 + 1));
        
    }
}