#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <signal.h>
#include <locale.h> //LC_ALL
#include <regex.h>              //regex

#include "unicode.h"
#include "./mytools/log.h"
#include "./mytools/mytools.h"


#ifndef SUCCESS
#define SUCCESS 1
#endif

#ifndef FAILE
#define FAILE 0
#endif


static void signal_exit(int sigmun)
{
    switch (sigmun) {
        case SIGINT:
            printf("recv SIGINT\n");    /* 中断 */
            break;
        case SIGTERM:
            printf("recv SIGTERM\n");   /* 终止 */
            break;
        case SIGSEGV:
            printf("recv SIGSEGV\n");   /* 无效内存引用 */
            break;
        case SIGABRT:
            printf("recv SIGABRT\n");   /* 异常终止 */
            break;
        case SIGBUS:
            printf("recv SIGBUS\n");    /* 硬件错误 */
            break;
        case SIGFPE:
            printf("recv SIGFPE\n");    /* 算术异常 */
            break;
        case SIGILL:
            printf("recv SIGILL\n");    /* 非法硬件指令 */
            break;
        default:
            printf("recv %d signal\n", sigmun);
            break;
    }

    /* release resource here */

    exit(1);
}

static void test_usage(void)
{
   printf("usage: cxx_test [-hd]                            \n");
   printf("       -h                    print help messages\n");
   printf("       -f                    platform info   \n");
   exit(0);
}

void signal_test(void)
{
    char *a = (char *)malloc(5);
    strcpy(a, "a");
    printf("a:%x %x", a, *a);
    free(a);
    printf("a:%x %x", a, *a);
    free(a);
    printf("a:%x %x", a, *a);
    printf("a:%x %x", a, *a);
}


void big_lit_duan()
{
    union utype
    {
        int i;
        char a;
    };
    union utype u;
    u.i = 1;

    if (u.a)
        printf("lit duan\n");
    else
        printf("big duan\n");    
}


void platform_info(void)
{
    big_lit_duan();
    printf("sizeof(long):%d \n", sizeof(long));
}

/*****************************************************************************
 函 数 名  : str_regex
 功能描述  : 正则表达式  匹配字符串
 输入参数  : u_char *src_str  
             u_char *pattern 正则表达式
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2016年12月8日
    作    者   : zj
    修改内容   : 新生成函数

*****************************************************************************/
BOOL str_regex(u_char * src_str, u_char * pattern)
{
    int     status, i;
    int     cflags = REG_EXTENDED;
    regmatch_t pmatch[1];
    const size_t nmatch = 1;
    regex_t reg;
    BOOL    bl_ret = FALSE;

    regcomp(&reg, pattern, cflags);     //编译正则模式
    status = regexec(&reg, src_str, nmatch, pmatch, 0); //执行正则表达式和缓存的比较
    if (status == REG_NOMATCH) {
        bl_ret = FALSE;
    } else if (0 == status) {
        bl_ret = TRUE;
    }
    regfree(&reg);
    return bl_ret;
}

#if 1
int main(int argc,char *argv[])
{ 
    int i;
    int i_ret;
    int i_opt;
    char buf[500];
    const char *pattern = "^((13[0-9])|(15[^4,\\D])|(18[0-9]))\\d{8}$";

    while ((i_opt = getopt(argc, argv, "hfe:")) != -1) {
        switch (i_opt) {
            case 'h':
                test_usage();
                break;
            case 'f':
                platform_info();
                break;
            case 'e':
                printf("str_regex:%d\n", str_regex(optarg, pattern));
                break;
            default:
                test_usage();
        }
    }
    test_usage();

}
#endif
