#include <stdio.h>  //
#include <string.h>

int surprise(char* format, char* array)
{
    const char* sur = "Surprise!";
    int f_len = strlen(format), s_len = strlen(sur);
    int cnt = 1, t = 0;
    while ('0' <= format[cnt] && format[cnt] <= '9') {
        t = t * 10 + format[cnt] - '0';
        cnt++;
    }
    cnt = t;
    // printf("%d\n", cnt);
    if (cnt >= s_len) strcpy(array, sur);
    else {
        char sub_str[20];
        for (int i = 0; i < cnt; i++) {
            sub_str[i] = sur[i];
        }
        strcpy(array, sub_str);
    }
    return cnt <= s_len ? cnt : s_len;
}

int main()
{
    char example_1[20];
    char example_2[20];

    int read_1 = surprise("%4s", example_1);
    int read_2 = surprise("%19s", example_2);

    printf("I copied %d characters: %s and %s", read_1 + read_2, example_1, example_2);
    return 0;
}