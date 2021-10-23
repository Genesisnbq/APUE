#include <stdio.h> 

int main() {
    char a[10];
    int b;
    double c;
    scanf("%s", a);
    scanf("%d", &b);
    scanf("%lf", &c);
    printf("%s今年%d岁， 期末考试考了%.1lf分", a, b, c);
    return 0;
}