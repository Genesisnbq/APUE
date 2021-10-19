# UNIX环境高级编程随书代码

## 第一章习题

1. 在系统上验证，除根目录外，目录.和..是不同的。

   ```c
   // 验证除根目录外， . 和 .. 是不同的
   #include <dirent.h>
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <unistd.h>
   
   void checkLs()
   {
       DIR* dp1, *dp2;
       struct dirent *dirp1, *dirp2;
   
       char *dir1 = ".";
       char *dir2 = "..";
   
       if ((dp1 = opendir(dir1)) == NULL) {
           printf("can't open %s", dir1);
       }
   
       if ((dp2 = opendir(dir2)) == NULL) {
           printf("can't open %s", dir2);
       }
   
       while ((dirp1 = readdir(dp1)) != NULL && (dirp2 = readdir(dp2)) != NULL) {
           if (strcmp(dirp1->d_name, dirp2->d_name) != 0) {
               printf("%s 与 %s 目录内文件不同\n", dir1, dir2);
               closedir(dp1);
               closedir(dp2);
               return;
           }
       }
       printf("%s 与 %s 目录内文件相同\n", dir1, dir2);
       closedir(dp1);
       closedir(dp2);
   }
   
   void checkPwd()
   {
       char path1[1024], path2[1024];
       realpath(".", path1);
       realpath("..", path2);
       if (strcmp(path1, path2) == 0) {
           printf("%s 与 %s 的绝对路径相同\n", path1, path2);
       } else {
           printf("%s 与 %s 的绝对路径不同\n", path1, path2);
       }
   }
   
   int main(int argc, char* argv[])
   {
       checkLs();
       checkPwd();
       exit(0);
   }
   ```

   

2. 分析图16程序的输出，说明进程ID为852和853的进程发生了什么情况？

   Unix系统下，系统按顺序分配PID， 第一次运行和第二次运行期间，系统里创建了两个新的进程 

3. 在1.7节中，perror的参数是用ISO C的属性const定义的，而strerror的整型参数没有用此属性定义，为什么？

   ```c
   #include <string.h>
   char *strerror(int errnum);
   
   #include <stdio.h>
   void perror(const char *msg);
   ```

   `strerror` 传递的参数为 `int` 类型，将会在对应的函数内复制一份，因此不会修改原来参数的值

   `perror` 传递的参数为 `const char *` 类型，传递的是对应的地址，如果不使用 `const` 限定的话，那么如果在函数内修改了值，函数外的变量值也会变化

4. 若日历时间存放在带符号的32位整型数中，那么到哪一年它将溢出？可以用什么方法扩展溢出浮点数？采用的策略是否与现有的应用相兼容？

   32 位整型数的最大值为 2147483647 ，大概为 68.09626 年。通过查询可知，最大可表示到 2038-01-19 11:14:07

   使用 IEEE754 编码扩展（double），与现有的应用不一定兼容。

   ```c
   #include <stdio.h>
   
   const int max = ~(1 << 31);
   
   int main()
   {
       printf("%f\n", max * 1.0 / 100 / 60 / 60 / 24);
       return 0;
   }
   ```

5. 若进程时间存放在带符号的32位整型数中，而且每秒为100时钟滴答，那么经过多少天后该时间值将会溢出?

   ```c
   #include <stdio.h>
   
   const int max = ~(1 << 31);
   
   int main()
   {
       printf("%f\n", max * 1.0 / 100 / 60 / 60 / 24);
       return 0;
   }
   ```

   



