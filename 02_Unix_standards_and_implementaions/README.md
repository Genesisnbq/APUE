# UNIX环境高级编程随书代码

## 习题

1. 在2.8节中提到一些基本系统数据类型可以在多个头文件中定义。例如，在FreeBSD8.0中，size_t在29个不同的头文件中都有定义。由于一个程序可能包含这29个不同的头文件，但是ISOC却不允许对同一个名字进行多次typedef，那么如何编写这些头文件呢？

   ```c
   #ifndef _MACHINE_TYPES_H_
   #define _MACHINE_TYPES_H_
   
   typedef int _int32_t;
   typedef unsigned int _uint32_t;
   
   .........
   
   typedef _uint32_t _size_t;
   
   .........
   
   #enddef
   ```

2. 检查系统的头文件，列出实现基本系统数据类型所用到的实际数据类型。

3. 改写图217中的程序，使其在sysconf为OPEN_MAX限制返回LONG_MAX时，避免进行不必要的处理。

   在 `sysconf` 没有能够准确获得 `OPEN_MAX` 限制的时候，可以使用 `getrlimit` 来获得。

   ```c
   long open_max()
   {
       struct rlimit rl;
       if (openmax == 0){
           errno = 0;
   
       if ((openmax = sysconf(_SC_OPEN_MAX)) < 0 || openmax == LONG_MAX) {
               if ((openmax = getrlimit(RLIMIT_NOFILE, &rl)) < 0) {
                   err_sys("can not get file limit\n");
               } else if (openmax == RLIM_INFINITY)
                   openmax = OPEN_MAX_GUESS;
               else
                   openmax = rl.rlim_max;
           }
       }
       return(openmax);
   }
   ```
