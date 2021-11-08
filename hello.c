#include <stdio.h> // for printf
#include <string.h>

char str[100010];

int main() {
    scanf("%[^\n]s", str);
    for (int i = 0; i < strlen(str); i ++) {
        if ('a' <= str[i] && str[i] <= 'z') printf("%c", str[i]);
        if ('A' <= str[i] && str[i] <= 'Z') printf("%c", str[i]);
    }
    return 0;
}