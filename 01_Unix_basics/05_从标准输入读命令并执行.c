#include "apue.h"
#include <sys/wait.h>

int main()
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    /*
        •用标准I/O函数fgets从标准输入一次读取一行。
        当键入文件结束符（通常是Ctrl+D）作为行的第一个字符时，
        fgets返回一个null指针，于是循环停止，进程也就终止。
    */
    /*
        •因为fgets返回的每一行都以换行符终止，后随一个null字节，
        因此用标准C函数strlen计算此字符串的长度，然后用一个null字节替换换行符。
        这样做是因为execlp函数要求的参数是以null结束的而不是以换行符结束的。
    */
    /*
        •调用fork创建一个新进程。新进程是调用进程的一个副本，我们称调用进程为父进程，
        新创建的进程为子进程。fork对父进程返回新的子进程的进程ID（一个非负整数），
        对子进程则返回0。因为fork创建一个新进程，所以说它被调用一次（由父进程），
        但返回两次（分别在父进程中和在子进程中）。
    */
    /*
        在子进程中，调用execlp以执行从标准输入读入的命令。这就用新的程序文件替换了子进程原先执行的程序文件。
        fork和跟随其后的exec两者的组合就是某些操作系统所称的产生（spawn）一个新进程。
        在UNIX系统中，这两部分分离成两个独立的函数。
    */
    /*
        子进程调用execlp执行新程序文件，而父进程希望等待子进程终止，这是通过调用waitpid实现的，
        其参数指定要等待的进程（即pid参数是子进程ID）。
        waitpid函数返回子进程的终止状态（status变量）。
        在我们这个简单的程序中，没有使用该值。如果需要，可以用此值准确地判定子进程是如何终止的。
    */
    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n') {
            // 因为execlp要求参数以null结束， 而不是换行符
            buf[strlen(buf) - 1] = 0; /* replace newline with null */
        }
        // 调用 fork 创建一个新的进程
        pid = fork();
        if (pid < 0) {
            err_sys("fork error");
        }
        else if (pid == 0) {
            execlp(buf, buf, (char*)0);
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }
        /* parent */
        pid = waitpid(pid, &status, 0);
        if (pid < 0) {
            err_sys("waitpid error");
        }
        printf("%% ");
    }
    exit(0);
}