/*
    我理解的题意: 给定一个假设完全随机的函数rand(), 可以生成1-n之间的随机数
    如何生成一个输出1-n中所有数字的随机排列，要保证未出现的数字出现的概率也一样

    因为给定了需要使用randn()函数, 无法使用乱序打乱数组的思路了
*/
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

bool st[1000005];
int ans[1000005];

int randn(int n)
{
    return rand() % n + 1;
}

// 最开始的想法
void solve1(int n)
{
    int cnt = 0, k = 0;
    while (cnt != n) {
        int t = randn(n);  // 生成 1~n之间的随机数
        if (!st[t]) {
            ans[k++] = t;
            st[t] = true;
            cnt++;
        }
    }
    for (int i = 0; i < n; i++) {
        i > 0 && printf(" ");
        printf("%d", ans[i]);
    }
    puts("");
}

/*
    我后面仔细想想， 如果randn() 函数是生成 1 ~ n之间的随机数， 那么未出现的数字出现的概率也是一样的
    都应该是 1/n.

    但是随机数的生成虽然是随机的，循环产生重复的随机数虽然是小概率事件，但也依然存在。

    昨晚又做了一下rand5 to rand7  和 rand7 和 rand10
    有这么一个公式 rand7 = (rand5 * 5 + rand5) % 7 + 1 (然后将超过21的数字砍掉) 7的倍数
                 rand10 = (rand7 * 7 + rand7) % 10 + 1 (然后将超过40的数字砍掉) 10的倍数

    例如rand10：
        定义连续两次调用Rand7() 为一轮， 在第一轮中， 有40/49的概率被接受， 但是有9/49的概率被拒绝，进入
        下一轮随机；下一轮有 9/49 * 9/49 的概率被拒绝， 以此类推，第n轮被决绝的概率是 (9/49)^n
        因此调用Rand7()的期望次数为：
            = 2 + 2 * 9/49 + 2 * (9/49)^2 +...
            = 2 * 1 / (1 - 9/49)
            差不多是2.45
*/

/*
    回到这个问题：
        生成第一个数字的时候的概率是1， 不会被拒绝
        生成第二个数字， 被拒绝的概率是 1/n, 再次调用randn()被拒接的概率是 1/n * 1/n
        依次类推，第n次被拒绝的概率是 (1/n)^n

        生成第三个数字， 被拒绝的概率是 2/n
        同上， 第n次被拒绝的概率是 (2/n)^n

        生成第四个数字， 被拒绝的概率是 3/10
        同上， 第n次被拒绝的概率是 (3/n)^n

        因此所有数字在第n轮被拒绝的概率为
        = (1/n)^n + (2/n)^n + (3/n)^n+...((n-1)/n)^n
*/

/*
    另一种思路： 可以看成是 每次从 1 ~ n个数字中有放回地抽取一个数字，
    求： 直到所有球都被抽到至少一次，抽取次数的期望
    可以记 f(i) 表示还有i个数字没出现， f(n) = 0, 我们要求的是f(0)
    f(i - 1) = f(i) + n/i
    还有i-1个没出现 相对 还有i个没出现， 平均还需要随机多少次？ 只要有一次随机到了n个数字中的这i个之一就可以了。
    有放回， 每次这样随机的概率是p = i/n, 因此多随机到一个新的数字所需次数的数学期望是 = 1/p = n/i

    得到f(0) = 0 + n/n+ n/(n-1) + n/(n-2) +... + n/2 + n = n(1 + 1/2 + ... +1/n)

    当n=1000000的时候 f(0) = 14392726.722865 ≈ 1e7, 计算机可以 1秒内跑完
*/

/* =================================================================*/

/*
    方案2
    第一次输出K
    第二次输出的时候，我需要通过 randn 来实现 randEeceptK
    将概率均等地映射到 1 ~ k - 1, k + 1 ~ n


*/

int randm(int n, int m) {
    int x = ~(1 << 31);
    while (x > m) {
        x = randn(n);
    }
    return x;
}

void solve2(int n)
{
    int x = 0, cnt = 0;
    for (int i = 1; i <= n; i++) {
        x = (x + rand() % i) % i;
        if (x != 0)
            ans[cnt++] = x;
        else {
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", ans[i]);
    }
    puts("");
}

// 计算期望
double get_exp(int n)
{
    double sum = 1;
    for (int i = 2; i <= n; i++) {
        sum += 1.0 / i;
    }
    return sum * n;
}

int main()
{
    srand(time(NULL));
    puts("Enter a number n: ");
    int n;
    scanf("%d", &n);

    puts("Solution1:");
    solve1(n);

    printf("n = %d, exp = %lf\n", n, get_exp(n));

    // 方案2
    memset(st, false, sizeof st);
    puts("Solution2:");
    solve2(n);

    return 0;
}