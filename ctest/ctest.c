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
            printf("recv SIGINT\n");    /* �ж� */
            break;
        case SIGTERM:
            printf("recv SIGTERM\n");   /* ��ֹ */
            break;
        case SIGSEGV:
            printf("recv SIGSEGV\n");   /* ��Ч�ڴ����� */
            break;
        case SIGABRT:
            printf("recv SIGABRT\n");   /* �쳣��ֹ */
            break;
        case SIGBUS:
            printf("recv SIGBUS\n");    /* Ӳ������ */
            break;
        case SIGFPE:
            printf("recv SIGFPE\n");    /* �����쳣 */
            break;
        case SIGILL:
            printf("recv SIGILL\n");    /* �Ƿ�Ӳ��ָ�� */
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
 �� �� ��  : str_regex
 ��������  : ������ʽ  ƥ���ַ���
 �������  : u_char *src_str  
             u_char *pattern ������ʽ
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2016��12��8��
    ��    ��   : zj
    �޸�����   : �����ɺ���

*****************************************************************************/
BOOL str_regex(u_char * src_str, u_char * pattern)
{
    int     status, i;
    int     cflags = REG_EXTENDED;
    regmatch_t pmatch[1];
    const size_t nmatch = 1;
    regex_t reg;
    BOOL    bl_ret = FALSE;

    regcomp(&reg, pattern, cflags);     //��������ģʽ
    status = regexec(&reg, src_str, nmatch, pmatch, 0); //ִ��������ʽ�ͻ���ıȽ�
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
