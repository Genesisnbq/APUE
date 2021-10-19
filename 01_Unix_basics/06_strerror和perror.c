#include "apue.h"
#include <errno.h>

int main(int argc, char* argv[])
{
    /*
        char *strerror(int errnum);返回值：指向消息字符串的指针
        strerror 函数将errnum(通常就是errnod值）映射为一个出错消息字符串， 并且返回此字符串的指针。
    */
    fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
    errno = ENOENT;
    /*
        perror函数基于errno的当前值， 在标准错误上产生一条出错消息， 然后返回。
        #include <stdio.h>
        void perror(const char *msg);
        它首先输出由msg指向的字符串， 然后是一个冒号，一个空格，接着是对应于error值的出错消息， 最后是一个换行符。
    */
    /*
        这是一个标准的UNIX惯例。 使用这种方法， 在程序作为管道的一部分执行时， 例如：
        prog1 < inputfile | prog1 | prog3 > outputfile
        我们就能分清 3个程序中的哪一个产生了一条特定的出错消息
    */
    perror(argv[0]);
    exit(0);
}