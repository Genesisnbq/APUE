#include "apue.h"
#include <dirent.h>

int main(int argc, char* argv[])
{
    DIR* dp;
    struct dirent* dirp;
    if (argc != 2)  //说明参数不够
        err_quit("usage: ls directory_name");

    /* 不同系统的目录项 的 实际格式是不一样的， 因此使用opendir，
       readdir 和 closedir对目录进行处理
    */
    if ((dp = opendir(argv[1])) == NULL)  // 权限不够
        err_sys("can't open %s", argv[1]);
    while ((dirp = readdir(dp)) != NULL)  // 获取目录项
        printf("%s\n", dirp->d_name);
    closedir(dp);
    exit(0);
}