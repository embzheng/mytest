/*****************************************************************************
File name    : monitor.c
Description  : 
Author       : zj
Version      :
Date         : 2016��11��15��
Others       : 
History      : 
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
1) ����:      �޸���:
   ����:
2��...
 
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
 �� �� ��  : mac_tostr_ch
 ��������  : 16��չmac��ַת�ַ���
 �������  : u_char *p_mac_hex  
             const char chken   �ָ���  default '-'
             u_char *p_mac_str �ռ��ⲿ����  , ��С18
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2016��11��15��
    ��    ��   : zj
    �޸�����   : �����ɺ���

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
 �� �� ��  : mac_tostr
 ��������  : 16��չmac��ַת�ַ���
 �������  : u_char *p_mac_hex  
             u_char *p_mac_str �ռ��ⲿ���� , ��С18
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2016��11��15��
    ��    ��   : zj
    �޸�����   : �����ɺ���

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
 �� �� ��  : ip_tobin
 ��������  : ����� ip v4��ַתΪ ����
 �������  : const char *p_ip_str  
             u_char * p_ip_hex  �ⲿ����ռ䣬���ֽ�   
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2016��11��16��
    ��    ��   : zj
    �޸�����   : �����ɺ���

    Դ����:
    in_addr_t inet_addr(const char* strptr);
    ���أ����ַ�����Ч���ַ���ת��Ϊ32λ�����������ֽ����IPV4��ַ������ΪINADDR_NONE

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
 �� �� ��  : ipv6_tobin
 ��������  : ����� ip v6��ַתΪ ����
 �������  : const char *p_ip_str  
             u_char * p_ip_hex  �ⲿ����ռ䣬16�ֽ�   
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2016��11��16��
    ��    ��   : zj
    �޸�����   : �����ɺ���

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
 �� �� ��  : ip_tostr
 ��������  : int ��ipת��Ϊ�ַ���
 �������  : u_char *p_ip_hex       ip��ַ
             u_char * p_ip_str      �ⲿ����ռ䣬16�ֽ�   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2016��11��16��
    ��    ��   : zj
    �޸�����   : �����ɺ���

    Դ����:char *inet_ntoa (struct in_addr);
           ���޴�������inet_ntoa()����һ���ַ�ָ�롣����Ļ�������NULL��
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
 �� �� ��  : ipv6_tostr
 ��������  : int ��ipת��Ϊ�ַ���
 �������  : u_char *p_ip_hex       ip��ַ
             u_char * p_ip_str      �ⲿ����ռ䣬64�ֽ�   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2016��11��16��
    ��    ��   : zj
    �޸�����   : �����ɺ���

    Դ����:char *inet_ntoa (struct in_addr);
           ���޴�������inet_ntoa()����һ���ַ�ָ�롣����Ļ�������NULL��
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
 �� �� ��  : lr_trim
 ��������  : ȥ���ַ�����β�� \x20 \r \n �ַ�
 �������  : char *s  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2016��11��16��
    ��    ��   : zj
    �޸�����   : �����ɺ���

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
 �� �� ��  : get_ini_value
 ��������  : ��ȡini�ļ�����ֵ
 �������  : char *profile  �ļ���(config.ini)
             char *AppName  Ӧ����(mysql)   ���20�ֽ�
             char *KeyName  �����ֶ�(host)  ���20�ֽ�
             char *KeyVal   ����ֵ(192.168.0.0) ���50�ֽ�
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2016��11��16��
    ��    ��   : zj
    �޸�����   : �����ɺ���
ini �ļ�ʾ�� config.ini:
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
 �� �� ��  : get_time
 ��������  : ��ȡʱ���ַ���
 �������  : u_char *time_out  �ռ��ⲿ���䣬������32
              BOOL millisecond �Ƿ�ȷ������
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2016��12��6��
    ��    ��   : zj
    �޸�����   : �����ɺ���

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
 �� �� ��  : byte_to_hex_str
 ��������  : �ֽ���ת��Ϊʮ�������ַ���
 �������  : const unsigned char* source  
             char* dest  �ռ������ source ����!!!             
             int sourceLen                
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2016��12��8��
    ��    ��   : zj
    �޸�����   : �����ɺ���

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
 �� �� ��  : hex_str_to_byte
 ��������  : ʮ�������ַ���ת��Ϊ�ֽ���
 �������  : const char* source   
             unsigned char* dest  
             int sourceLen        
 �������  : ��
 �� �� ֵ  : ת����ɺ�ĳ���
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2016��12��8��
    ��    ��   : zj
    �޸�����   : �����ɺ���

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
 �� �� ��  : my_system
 ��������  : ��װsystem���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ִ�н��
             ������ : -1 
             ����ִ���쳣 : -1
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2014��3��21��
    ��    ��   : zj
    �޸�����   : �����ɺ���

*****************************************************************************/
int my_system(u_char *cmdstring)
{
    int     status;
    int     i_ret;
    /* ���cmdstringΪ�ճ������˰ɣ�����system()����Ҳ�ܴ����ָ�� */
    if (NULL == cmdstring) {
        return -1;
    }

    status = system(cmdstring);
    if (status < 0) {
        /* �������Ҫ��errno��Ϣ��������Log */
        perror("cmd exec error!"); 
        return -1;
    }  

    if (WIFEXITED(status)) {
        /* ȡ��cmdstringִ�н�� */
        i_ret = WEXITSTATUS(status);
        printf("normal termination, exit status = %d", i_ret);
    } else if (WIFSIGNALED(status)) {
        /* ���cmdstring���ź��жϣ�ȡ���ź�ֵ */
        i_ret = WTERMSIG(status);
        printf("abnormal termination,signal number =%d", i_ret);
    } else if (WIFSTOPPED(status)) {
        /* ���cmdstring���ź���ִͣ�У�ȡ���ź�ֵ */
        i_ret = WSTOPSIG(status);
        printf("process stopped, signal number =%d", i_ret);
    }
    
    return i_ret;
}
#endif
/*****************************************************************************
 �� �� ��  : my_split
 ��������  : �ָ��ַ������ŵ�����
 �������  : arr ���
             str �����ַ���
             del �ָ���
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��4��13��
    ��    ��   : zj
    �޸�����   : �����ɺ���

*****************************************************************************/
int my_split(char **arr, char *str, const char *del) {
    char *s = strtok(str, del);
    while(s != NULL) {
        *arr++ = s;
        s = strtok(NULL, del);
    }
}

/*****************************************************************************
 * ��һ���ַ���Unicode(UCS-2��UCS-4)����ת����UTF-8����.
 *
 * ����:
 *    unic     �ַ���Unicode����ֵ
 *    pOutput  ָ����������ڴ洢UTF8����ֵ�Ļ�������ָ��
 *    outsize  pOutput����Ĵ�С
 *
 * ����ֵ:
 *    ����ת������ַ���UTF8������ռ���ֽ���, ��������򷵻� 0 .
 *
 * ע��:
 *     1. UTF8û���ֽ�������, ����Unicode���ֽ���Ҫ��;
 *        �ֽ����Ϊ���(Big Endian)��С��(Little Endian)����;
 *        ��Intel�������в���С�˷���ʾ, �ڴ˲���С�˷���ʾ. (�͵�ַ���λ)
 *     2. �뱣֤ pOutput �������������� 6 �ֽڵĿռ��С!
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
 �� �� ��  : buffer_strstr
 ��������  : ��buf��������ַ���
 �������  : const char *buf  
             int buf_len      
             const char *s2   
 �������  : ��
 �� �� ֵ  : char
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2016��8��31��
    ��    ��   : zj
    �޸�����   : �����ɺ���

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
ȥ���ַ�����β�� \x20 \r \n �ַ�
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
 �� �� ��  : string_regex
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
BOOL string_regex(u_char * src_str, u_char * pattern)
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

/*****************************************************************************
 �� �� ��  : dump_to_buf
 ��������  : ��data��ӡ�����buf
 �������  : char *txt           
             const u_char *data  
             u_short len             
             u_char *buf_in  ������������ڴ��ⲿ����
             u_short *buf_len    ����buf_in���ȣ������ӡ�������    
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2016��11��15��
    ��    ��   : zj
    �޸�����   : �����ɺ���

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
 �� �� ��  : char_to_num
 ��������  : �ַ�ת����
 �������  : char ch  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��6��15��
    ��    ��   : zj
    �޸�����   : �����ɺ���

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
* ���ַ�������URL���롣 
* ���룺 
* str: Ҫ������ַ��� 
* strSize: �ַ����ĳ��ȡ� 
* result: ����������ĵ�ַ 
* resultSize:�����ַ�Ļ�������С������<=strSize 
* ����ֵ�� 
* >0: result��ʵ����Ч���ַ����ȣ� 
* 0: ����ʧ�ܣ�ԭ���ǽ��������result�ĳ���̫С 
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

