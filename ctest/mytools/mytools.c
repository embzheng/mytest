/*****************************************************************************
File name    : monitor.c
Description  : 
Author       : zj
Version      :
Date         : 2016年11月15日
Others       : 
History      : 
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
1) 日期:      修改者:
   内容:
2）...
 
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>         //AF_INET
#include <netinet/in.h>         //struct in_addr
#include <time.h>
#include <regex.h>              //regex

#include "mytools.h"


/*****************************************************************************
 函 数 名  : mac_tostr_ch
 功能描述  : 16进展mac地址转字符串
 输入参数  : u_char *p_mac_hex  
             const char chken   分隔符  default '-'
             u_char *p_mac_str 空间外部申请  , 最小18
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2016年11月15日
    作    者   : zj
    修改内容   : 新生成函数

*****************************************************************************/
void mac_tostr_ch(const u_char * p_mac_hex, const char chken, u_char * p_mac_str)
{
    int     i;
    char    szFormat[] = "%02X-%02X-%02X-%02X-%02X-%02X";

    int     nLen = strlen(szFormat);
    if (chken != '-') {
        for (i = 4; i < nLen; i += 5) {
            szFormat[i] = chken;
        }
    }
    sprintf(p_mac_str, szFormat, p_mac_hex[0], p_mac_hex[1], p_mac_hex[2],
            p_mac_hex[3], p_mac_hex[4], p_mac_hex[5]);
}
/*****************************************************************************
 函 数 名  : mac_tostr
 功能描述  : 16进展mac地址转字符串
 输入参数  : u_char *p_mac_hex  
             u_char *p_mac_str 空间外部申请 , 最小18
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2016年11月15日
    作    者   : zj
    修改内容   : 新生成函数

*****************************************************************************/
void mac_tostr(const u_char * p_mac_hex, u_char * p_mac_str)
{
    mac_tostr_ch(p_mac_hex, '-', p_mac_str);
}

u_char char_to_data(const char ch)
{
    switch (ch) {
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    case 'a':
    case 'A':
        return 10;
    case 'b':
    case 'B':
        return 11;
    case 'c':
    case 'C':
        return 12;
    case 'd':
    case 'D':
        return 13;
    case 'e':
    case 'E':
        return 14;
    case 'f':
    case 'F':
        return 15;
    }
    return 0;
}

void mac_tobin(const char *p_mac_str, u_char * p_mac_hex)
{
    int     i;
    const char *pTemp = p_mac_str;
    for (i = 0; i < 6; ++i) {
        p_mac_hex[i] = char_to_data(*pTemp++) * 16;
        p_mac_hex[i] += char_to_data(*pTemp++);
        pTemp++;
    }
}

/*****************************************************************************
 函 数 名  : ip_tobin
 功能描述  : 点分制 ip v4地址转为 整形
 输入参数  : const char *p_ip_str  
             u_char * p_ip_hex  外部分配空间，四字节   
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2016年11月16日
    作    者   : zj
    修改内容   : 新生成函数

    源函数:
    in_addr_t inet_addr(const char* strptr);
    返回：若字符串有效则将字符串转换为32位二进制网络字节序的IPV4地址，否则为INADDR_NONE

*****************************************************************************/
int ip_tobin(const char *p_ip_str, u_char * p_ip_hex)
{
    int     i_ret;

    i_ret = inet_pton(AF_INET, p_ip_str, p_ip_hex);
    if (i_ret < 0) {
        printf("inet_pton ip:%s err:%s", p_ip_str, strerror(errno));
        return FAILE;
    }

    if (i_ret = 0) {
        printf("ip:%s format err", p_ip_str);
        return FAILE;
    }
    return SUCCESS;
}

/*****************************************************************************
 函 数 名  : ipv6_tobin
 功能描述  : 点分制 ip v6地址转为 整形
 输入参数  : const char *p_ip_str  
             u_char * p_ip_hex  外部分配空间，16字节   
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2016年11月16日
    作    者   : zj
    修改内容   : 新生成函数

*****************************************************************************/
int ipv6_tobin(const char *p_ip_str, u_char * p_ip_hex)
{
    int     i_ret;

    i_ret = inet_pton(AF_INET6, p_ip_str, p_ip_hex);
    if (i_ret < 0) {
        printf("inet_pton ip:%s err:%s", p_ip_str, strerror(errno));
        return FAILE;
    }

    if (i_ret = 0) {
        printf("ip:%s format err", p_ip_str);
        return FAILE;
    }
    return SUCCESS;
}


/*****************************************************************************
 函 数 名  : ip_tostr
 功能描述  : int 型ip转换为字符串
 输入参数  : u_char *p_ip_hex       ip地址
             u_char * p_ip_str      外部分配空间，16字节   
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2016年11月16日
    作    者   : zj
    修改内容   : 新生成函数

    源函数:char *inet_ntoa (struct in_addr);
           若无错误发生，inet_ntoa()返回一个字符指针。否则的话，返回NULL。
*****************************************************************************/
int ip_tostr(u_char *p_ip_hex, u_char * p_ip_str)
{
    if (inet_ntop(AF_INET, p_ip_hex, p_ip_str, 16) == NULL) {
        printf("inet_ntop ip:%x err:%s", p_ip_hex, strerror(errno));
        return FAILE;
    }
    return SUCCESS;
}

/*****************************************************************************
 函 数 名  : ipv6_tostr
 功能描述  : int 型ip转换为字符串
 输入参数  : u_char *p_ip_hex       ip地址
             u_char * p_ip_str      外部分配空间，64字节   
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2016年11月16日
    作    者   : zj
    修改内容   : 新生成函数

    源函数:char *inet_ntoa (struct in_addr);
           若无错误发生，inet_ntoa()返回一个字符指针。否则的话，返回NULL。
*****************************************************************************/
int ipv6_tostr(u_char *p_ip_hex, u_char * p_ip_str)
{
    if (inet_ntop(AF_INET6, p_ip_hex, p_ip_str, 64) == NULL) {
        printf("inet_ntop ip:%x err:%s", p_ip_hex, strerror(errno));
        return FAILE;
    }
    return SUCCESS;
}


/*****************************************************************************
 函 数 名  : lr_trim
 功能描述  : 去掉字符串首尾的 \x20 \r \n 字符
 输入参数  : char *s  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2016年11月16日
    作    者   : zj
    修改内容   : 新生成函数

*****************************************************************************/
void str_lr_trim(char *s)
{
    int     i;
    char   *start = s;
    char   *end;
    int     s_len;

    s_len = strlen(start);
    for (i = 0; i < s_len; i++) {
        if (s[i] == ' ' || s[i] == '\r' || s[i] == '\n') {
            start++;
        } else {
            break;
        }
    }

    s_len = strlen(start);
    end = start + s_len;
    for (i = s_len - 1; i >= 0; i--) {
        if (start[i] == ' ' || start[i] == '\r' || start[i] == '\n') {
            end--;
        } else {
            break;
        }
    }

    memmove(s, start, end - start);
    *end = 0;
}

/*****************************************************************************
 函 数 名  : get_ini_value
 功能描述  : 获取ini文件配置值
 输入参数  : char *profile  文件名(config.ini)
             char *AppName  应用名(mysql)   最大20字节
             char *KeyName  配置字段(host)  最大20字节
             char *KeyVal   配置值(192.168.0.0) 最大50字节
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2016年11月16日
    作    者   : zj
    修改内容   : 新生成函数
ini 文件示例 config.ini:
[mysql]
host=192.168.0.0
user=test
password=test
db=testdb
port=3306
*****************************************************************************/
int get_ini_value(char *profile, char *AppName, char *KeyName, char *KeyVal)
{
    char    appname[20], keyname[20];
    char    buf[100], *c;
    FILE   *fp;
    int     found = 0;

    if ((fp = fopen(profile, "r")) == NULL) {
        printf("openfile [%s] error [%s]\n", profile, strerror(errno));
        return FAILE;
    }
    fseek(fp, 0, SEEK_SET);

    sprintf(appname, "[%s]", AppName);
    memset(keyname, 0, sizeof(keyname));

    while (!feof(fp) && fgets(buf, 100, fp) != NULL) {
        //if( l_trim( buf )==0 )
        //continue;

        if (found == 0) {
            if (buf[0] != '[') {
                continue;
            } else if (strncmp(buf, appname, strlen(appname)) == 0) {
                found = 1;
                continue;
            }
        } else if (found == 1) {
            if (buf[0] == '#') {
                continue;
            } else if (buf[0] == '[') {
                break;
            } else {
                if ((c = (char *) strchr(buf, '=')) == NULL)
                    continue;
                memset(keyname, 0, sizeof(keyname));
                sscanf(buf, "%[^=]", keyname);
                if (strcmp(keyname, KeyName) == 0) {
                    sscanf(++c, "%[^\n]", KeyVal);
                    str_lr_trim(KeyVal);
                    found = 2;
                    break;
                } else {
                    continue;
                }
            }
        }
    }

    fclose(fp);

    if (found == 2)
        return SUCCESS;
    else
        return FAILE;
}


/*****************************************************************************
 函 数 名  : get_time
 功能描述  : 获取时间字符串
 输入参数  : u_char *time_out  空间外部分配，不少于32
              BOOL millisecond 是否精确到毫秒
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2016年12月6日
    作    者   : zj
    修改内容   : 新生成函数

*****************************************************************************/
int get_time(u_char * time_out, BOOL millisecond)
{
    struct timeval tv;
    struct tm *pst_tm = NULL;
    char    timestamp[32] = { 0 };

    gettimeofday(&tv, NULL);
    pst_tm = localtime(&tv.tv_sec);

    if (pst_tm == NULL) {
        return FAILE;
    }
    
    if (millisecond) {
        snprintf(time_out, 32, "%02d-%02d-%02d %02d:%02d:%02d.%03d",
                 pst_tm->tm_year + 1900,
                 pst_tm->tm_mon + 1, pst_tm->tm_mday,
                 pst_tm->tm_hour, pst_tm->tm_min, pst_tm->tm_sec, tv.tv_usec / 1000);
    } else {
        snprintf(time_out, 32, "%02d-%02d-%02d %02d:%02d:%02d",
                 pst_tm->tm_year + 1900,
                 pst_tm->tm_mon + 1, pst_tm->tm_mday, pst_tm->tm_hour, pst_tm->tm_min,
                 pst_tm->tm_sec);
    }
    return SUCCESS;
}

/*****************************************************************************
 函 数 名  : byte_to_hex_str
 功能描述  : 字节流转换为十六进制字符串
 输入参数  : const unsigned char* source  
             char* dest  空间必须是 source 两倍!!!             
             int sourceLen                
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2016年12月8日
    作    者   : zj
    修改内容   : 新生成函数

*****************************************************************************/
void byte_to_hex_str(const unsigned char *source, char *dest, int sourceLen)
{
    short   i;
    unsigned char highByte, lowByte;

    for (i = 0; i < sourceLen; i++) {
        highByte = source[i] >> 4;
        lowByte = source[i] & 0x0f;

        highByte += 0x30;

        if (highByte > 0x39)
            dest[i * 2] = highByte + 0x07;
        else
            dest[i * 2] = highByte;

        lowByte += 0x30;
        if (lowByte > 0x39)
            dest[i * 2 + 1] = lowByte + 0x07;
        else
            dest[i * 2 + 1] = lowByte;
    }
    return;
}

/*****************************************************************************
 函 数 名  : hex_str_to_byte
 功能描述  : 十六进制字符串转换为字节流
 输入参数  : const char* source   
             unsigned char* dest  
             int sourceLen        
 输出参数  : 无
 返 回 值  : 转换完成后的长度
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2016年12月8日
    作    者   : zj
    修改内容   : 新生成函数

*****************************************************************************/
int hex_str_to_byte(const char *source, unsigned char *dest, int sourceLen)
{
    short   i;
    unsigned char highByte, lowByte;

    for (i = 0; i < sourceLen; i += 2) {
        highByte = toupper(source[i]);
        lowByte = toupper(source[i + 1]);

        if (highByte > 0x39)
            highByte -= 0x37;
        else
            highByte -= 0x30;

        if (lowByte > 0x39)
            lowByte -= 0x37;
        else
            lowByte -= 0x30;

        dest[i / 2] = (highByte << 4) | lowByte;
    }
    return sourceLen / 2;
}
#if 0
/*****************************************************************************
 函 数 名  : my_system
 功能描述  : 封装system结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 命令执行结果
             空命令 : -1 
             命令执行异常 : -1
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2014年3月21日
    作    者   : zj
    修改内容   : 新生成函数

*****************************************************************************/
int my_system(u_char *cmdstring)
{
    int     status;
    int     i_ret;
    /* 如果cmdstring为空趁早闪退吧，尽管system()函数也能处理空指针 */
    if (NULL == cmdstring) {
        return -1;
    }

    status = system(cmdstring);
    if (status < 0) {
        /* 这里务必要把errno信息输出或记入Log */
        perror("cmd exec error!"); 
        return -1;
    }  

    if (WIFEXITED(status)) {
        /* 取得cmdstring执行结果 */
        i_ret = WEXITSTATUS(status);
        printf("normal termination, exit status = %d", i_ret);
    } else if (WIFSIGNALED(status)) {
        /* 如果cmdstring被信号中断，取得信号值 */
        i_ret = WTERMSIG(status);
        printf("abnormal termination,signal number =%d", i_ret);
    } else if (WIFSTOPPED(status)) {
        /* 如果cmdstring被信号暂停执行，取得信号值 */
        i_ret = WSTOPSIG(status);
        printf("process stopped, signal number =%d", i_ret);
    }
    
    return i_ret;
}
#endif
/*****************************************************************************
 函 数 名  : my_split
 功能描述  : 分割字符串，放到数组
 输入参数  : arr 结果
             str 输入字符串
             del 分隔符
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年4月13日
    作    者   : zj
    修改内容   : 新生成函数

*****************************************************************************/
int my_split(char **arr, char *str, const char *del) {
    char *s = strtok(str, del);
    while(s != NULL) {
        *arr++ = s;
        s = strtok(NULL, del);
    }
}

/*****************************************************************************
 * 将一个字符的Unicode(UCS-2和UCS-4)编码转换成UTF-8编码.
 *
 * 参数:
 *    unic     字符的Unicode编码值
 *    pOutput  指向输出的用于存储UTF8编码值的缓冲区的指针
 *    outsize  pOutput缓冲的大小
 *
 * 返回值:
 *    返回转换后的字符的UTF8编码所占的字节数, 如果出错则返回 0 .
 *
 * 注意:
 *     1. UTF8没有字节序问题, 但是Unicode有字节序要求;
 *        字节序分为大端(Big Endian)和小端(Little Endian)两种;
 *        在Intel处理器中采用小端法表示, 在此采用小端法表示. (低地址存低位)
 *     2. 请保证 pOutput 缓冲区有最少有 6 字节的空间大小!
 ****************************************************************************/
int enc_unicode_to_utf8_one(unsigned long unic, unsigned char *pOutput,
        int outSize)
{
    //assert(pOutput != NULL);
    //assert(outSize >= 6);

    if ( unic <= 0x0000007F )
    {
        // * U-00000000 - U-0000007F:  0xxxxxxx
        *pOutput     = (unic & 0x7F);
        return 1;
    }
    else if ( unic >= 0x00000080 && unic <= 0x000007FF )
    {
        // * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
        *(pOutput+1) = (unic & 0x3F) | 0x80;
        *pOutput     = ((unic >> 6) & 0x1F) | 0xC0;
        return 2;
    }
    else if ( unic >= 0x00000800 && unic <= 0x0000FFFF )
    {
        // * U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
        *(pOutput+2) = (unic & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >>  6) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 12) & 0x0F) | 0xE0;
        return 3;
    }
    else if ( unic >= 0x00010000 && unic <= 0x001FFFFF )
    {
        // * U-00010000 - U-001FFFFF:  11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(pOutput+3) = (unic & 0x3F) | 0x80;
        *(pOutput+2) = ((unic >>  6) & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >> 12) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 18) & 0x07) | 0xF0;
        return 4;
    }
    else if ( unic >= 0x00200000 && unic <= 0x03FFFFFF )
    {
        // * U-00200000 - U-03FFFFFF:  111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(pOutput+4) = (unic & 0x3F) | 0x80;
        *(pOutput+3) = ((unic >>  6) & 0x3F) | 0x80;
        *(pOutput+2) = ((unic >> 12) & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >> 18) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 24) & 0x03) | 0xF8;
        return 5;
    }
    else if ( unic >= 0x04000000 && unic <= 0x7FFFFFFF )
    {
        // * U-04000000 - U-7FFFFFFF:  1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(pOutput+5) = (unic & 0x3F) | 0x80;
        *(pOutput+4) = ((unic >>  6) & 0x3F) | 0x80;
        *(pOutput+3) = ((unic >> 12) & 0x3F) | 0x80;
        *(pOutput+2) = ((unic >> 18) & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >> 24) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 30) & 0x01) | 0xFC;
        return 6;
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : buffer_strstr
 功能描述  : 从buf里面查找字符串
 输入参数  : const char *buf  
             int buf_len      
             const char *s2   
 输出参数  : 无
 返 回 值  : char
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2016年8月31日
    作    者   : zj
    修改内容   : 新生成函数

*****************************************************************************/
char   *buffer_strstr(const char *buf, int buf_len, const char *s2)
{
    int     len2;
    int     i;

    if (buf == NULL) {
        return NULL;
    }

    if (s2 == NULL) {
        return NULL;
    }

    if (buf_len == 0) {
        return NULL;
    }

    len2 = strlen(s2);
    if (len2 == 0) {
        return NULL;
    }

    for (i = 0; i < (buf_len - len2); i++) {
        if (buf[i] == *s2 && strncmp(&buf[i], s2, len2) == 0) {
            return (char *) &buf[i];
        }
    }
    return NULL;
}
/*
去掉字符串首尾的 \x20 \r \n 字符
*/
void str_trim(char *s)
{
    int     i;
    char   *start = s;
    char   *end;
    int     s_len;

    s_len = strlen(start);
    for (i = 0; i < s_len; i++) {
        if (s[i] == ' ' || s[i] == '\r' || s[i] == '\n') {
            start++;
        } else {
            break;
        }
    }

    s_len = strlen(start);
    end = start + s_len;
    for (i = s_len - 1; i >= 0; i--) {
        if (start[i] == ' ' || start[i] == '\r' || start[i] == '\n') {
            end--;
        } else {
            break;
        }
    }

    memmove(s, start, end - start);
    *end = 0;
}
/*****************************************************************************
 函 数 名  : string_regex
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
BOOL string_regex(u_char * src_str, u_char * pattern)
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

/*****************************************************************************
 函 数 名  : dump_to_buf
 功能描述  : 把data打印输出到buf
 输入参数  : char *txt           
             const u_char *data  
             u_short len             
             u_char *buf_in  存放输出结果，内存外部申请
             u_short *buf_len    输入buf_in长度，输出打印结果长度    
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2016年11月15日
    作    者   : zj
    修改内容   : 新生成函数

*****************************************************************************/
void dump_to_buf(char *txt, const u_char * data, u_short len, u_char * buf_in, u_short * buf_len)
{
    int     i, j;
    char    buf[100];
    int     l;
    u_int   offset = 0;

    if (len == 0) {
        *buf_len = 0;
        return;
    }

    memset(buf, 0, sizeof(buf));
    memset(buf_in, 0, *buf_len);

    offset += snprintf(buf_in + offset, *buf_len - offset, "%s len=%d \n", txt, len);

    for (i = 0; i < len; i += 16) {
        l = 0;
        l += snprintf(buf + l, sizeof(buf) - l, "%04X  ", i);
        for (j = i; (j < i + 16); j++) {
            if (j < len) {
                l += snprintf(buf + l, sizeof(buf) - l, "%02X ", (unsigned char) *(data + j));
            } else {
                l += snprintf(buf + l, sizeof(buf) - l, "   ");
            }
        }

        l += snprintf(buf + l, sizeof(buf) - l, "  ");

        for (j = i; (j < i + 16) && (j < len); j++) {
            if ((*(data + j) >= 32) && (*(data + j) <= 127)) {
                l += snprintf(buf + l, sizeof(buf) - l, "%c", *(data + j));
            } else {
                l += snprintf(buf + l, sizeof(buf) - l, ".");
            }
        }

        l += snprintf(buf + l, sizeof(buf) - l, "\n");
        offset += snprintf(buf_in + offset, *buf_len - offset, "%s", buf);
    }
    *buf_len = offset;
    return;

}



/*****************************************************************************
 函 数 名  : char_to_num
 功能描述  : 字符转数字
 输入参数  : char ch  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年6月15日
    作    者   : zj
    修改内容   : 新生成函数

*****************************************************************************/
char char2num(char ch)
{
    if (ch >= '0' && ch <= '9')
        return (char) (ch - '0');
    if (ch >= 'a' && ch <= 'f')
        return (char) (ch - 'a' + 10);
    if (ch >= 'A' && ch <= 'F')
        return (char) (ch - 'A' + 10);
    return '0';
}

/************************************************ 
* 把字符串进行URL解码。 
* 输入： 
* str: 要解码的字符串 
* strSize: 字符串的长度。 
* result: 结果缓冲区的地址 
* resultSize:结果地址的缓冲区大小，可以<=strSize 
* 返回值： 
* >0: result中实际有效的字符长度， 
* 0: 解码失败，原因是结果缓冲区result的长度太小 
************************************************/
int decode_url(const char *str, const int strSize, char *result, const int resultSize)
{
    char    ch, ch1, ch2;
    int     i;
    int     j = 0;              /* for result index */
#define NON_NUM '0'

    if ((str == NULL) || (result == NULL) || (strSize <= 0) || (resultSize <= 0)) {
        return 0;
    }

    for (i = 0; (i < strSize) && (j < resultSize); i++) {
        ch = str[i];
        switch (ch) {
        case '+':
            result[j++] = ' ';
            break;

        case '%':
            if (i + 2 < strSize) {
                ch1 = char2num(str[i + 1]);
                ch2 = char2num(str[i + 2]);
                if ((ch1 != NON_NUM) && (ch2 != NON_NUM)) {
                    result[j++] = (char) ((ch1 << 4) | ch2);

                    i += 2;
                    break;
                }
            }

        /* goto default */
        default:
            result[j++] = ch;
            break;
        }
    }

    result[j] = '\0';
    return j;
}

