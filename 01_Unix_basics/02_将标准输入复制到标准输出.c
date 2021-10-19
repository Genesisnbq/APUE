#include "apue.h"

#define BUFFSIZE 4096

int main(void)
{
    int n;
    char buf[BUFFSIZE];

    /*
        read返回读取的字节数， 到达输入文件的尾端时， read返回0， 程序停止执行。
        读取过程中被信号打断， 返回读取的字符数
        如果发生读错误， read返回-1.
    */
    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            err_sys("write_error");
        }
    }
    if (n < 0)
        err_sys("read_error");
    exit(0);
}
