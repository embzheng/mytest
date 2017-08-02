/*****************************************************************************
File name    : tlvanalyse.h
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
#ifndef __MYTOOLS_H__
#define __MYTOOLS_H__

#ifndef TYPEDEF_BOOL
#define TYPEDEF_BOOL
typedef unsigned char BOOL;
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef SUCCESS
#define SUCCESS 1
#endif

#ifndef FAILE
#define FAILE 0
#endif

#define MAX_MAC_STR_LEN             18  /* 最大字符串mac地址长度 */
#define MAX_IP_STR_LEN              64  /* 最大IP地址长度 */


#ifndef MAC2STR
#define MAC2STR(a) (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5]
#define MACSTR "%02x:%02x:%02x:%02x:%02x:%02x"
#endif

/* 大小端切换 */
#define BIG_LIT_SWAP16(A)  ((((u_short)(A) & 0xff00) >> 8) | (((u_short)(A) & 0x00ff) << 8))

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
int ip_tostr(u_char *p_ip_hex, u_char * p_ip_str);

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
void mac_tostr(const u_char * p_mac_hex, u_char * p_mac_str);



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
int     get_ini_value(char *profile, char *AppName, char *KeyName, char *KeyVal);


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
int     get_time(u_char * time_out, BOOL millisecond);

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
int     hex_str_to_byte(const char *source, unsigned char *dest, int sourceLen);

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
int my_system(u_char *cmdstring);


#endif
