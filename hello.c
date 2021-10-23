#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum STATE {
    DEFAULT,
    SQUOTE,  // 单引号
    DQUOTE,  // 双引号
    STATE1,  // 状态1
    BLOCKCMT,  // 块注释
    LINECMT,  // 行注释
    STATE2,  // 状态2
    ESCAPED,  // 转义状态（暂时只转义1个字符）
};

// 4MB
char buffer[4 * 1024 * 1024];

#ifdef DEBUG
#    define LOG(fmt) printf(fmt "\n");
#else
#    define LOG(fmt)
#endif

int main(int argc, char** argv)
{
    if (argc != 2) {
        printf("usage: comment-cleaner sample.c\n");
        return EXIT_FAILURE;
    }

    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("invalid file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    // fsize表示实际读入大小
    int fsize = fread(buffer, sizeof(char), 4 * 1024 * 1024, fp);
    int state = DEFAULT;

    int i = 0;
    while (i < fsize) {
        switch (buffer[i]) {
            case '/':
                if (state == DEFAULT) {
                    state = STATE1;
                    LOG("state1");
                }
                else if (state == STATE1) {
                    state = LINECMT;
                    LOG("linecmt");
                }
                else if (state == STATE2) {
                    state = DEFAULT;
                    LOG("default");
                }
                else if (state != LINECMT && state != BLOCKCMT) {
                    printf("%c", buffer[i]);
                }
                i++;
                break;
            case '*':
                if (state == STATE1) {
                    state = BLOCKCMT;
                    LOG("blockcmt");
                }
                else if (state == BLOCKCMT) {
                    state = STATE2;
                    LOG("state2");
                }
                else if (state != LINECMT) {
                    printf("%c", buffer[i]);
                }
                i++;
                break;
            case '\"':
                if (state == DEFAULT || state == STATE1) {
                    state = DQUOTE;
                    LOG("dquote");
                    printf("%c", buffer[i]);
                }
                else if (state == DQUOTE) {
                    state = DEFAULT;
                    LOG("default");
                    printf("%c", buffer[i]);
                }
                else if (state != LINECMT && state != BLOCKCMT && state != STATE2) {
                    printf("%c", buffer[i]);
                }
                i++;
                break;
            case '\'':
                if (state == DEFAULT || state == STATE1) {
                    state = SQUOTE;
                    LOG("squote");
                    printf("%c", buffer[i]);
                }
                else if (state == SQUOTE) {
                    state = DEFAULT;
                    LOG("default");
                    printf("%c", buffer[i]);
                }
                else if (state != LINECMT && state != BLOCKCMT && state != STATE2) {
                    printf("%c", buffer[i]);
                }
                i++;
                break;
            case '\\':
                if (state != BLOCKCMT && state != LINECMT && state != STATE2) {
                    i += 2;
                    LOG("escaped");
                    printf("%c%c", buffer[i - 2], buffer[i - 1]);
                }
                break;
            case '\n':
                if (state == LINECMT) {
                    state = DEFAULT;
                    LOG("default");
                    printf("%c", buffer[i]);
                }
                else if (state != BLOCKCMT && state != STATE2) {
                    printf("%c", buffer[i]);
                }
                i++;
                break;
            default:
                if (state != LINECMT && state != BLOCKCMT && state != STATE2)
                    printf("%c", buffer[i]);
                i++;
                break;
        }
    }

    return EXIT_SUCCESS;
}
