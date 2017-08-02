#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <signal.h>
#include <fcntl.h>
#include <iostream>
using namespace std;


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

static void help_usage(void)
{
   cout << "usage: file_factory [-h]                            " << endl;
   cout << "       -h                     print help messages  " << endl;
   cout << "       插入操作: 先在需要插入的文件的相应位置写入‘file_factory’字符串，" << endl;
   cout << "                 然后执行以下命令:" << endl;
   cout << "                 file_factory [src_file] [ins_file] [loop_num]" << endl;
   cout << "                 src_file 为源文件，ins_file为插入文件，loop_num为插入循环次数" << endl;
   cout << "       修改操作: 敲入以下命令:" << endl;
   cout << "                 file_factory [src_file] [findstr] [ins_num] [grow]" << endl;
   cout << "                 src_file 为源文件，findstr为需要修改的字符串，ins_num为修改写入" << endl;
   cout << "                 的数字，注意该数字的长度需小于需要修改的字符串, 修改写入" << endl;
   cout << "                 的数字替换至findstr末尾" << endl;
   
   exit(0);
}

static void help_usage_en(void)
{
   cout << "usage: file_factory                           " << endl; 
   cout << "               file_factory [src_file] [ins_file] [loop_num]" << endl;
   cout << "               file_factory [src_file] [findstr] [ins_num] [grow]" << endl;
   cout << "                " << endl;
   cout << "       Insert: first in the corresponding position of the file to be inserted, Write" << endl;
   cout << "               a string 'file_factory', And then execute the following command" << endl;
   cout << "               file_factory [src_file] [ins_file] [loop_num]" << endl;
   cout << "               src_file is the source file, ins_file is the insert file, loop_num is " << endl;
   cout << "               the insert the number of times" << endl;
   cout << "       Modify: execute the following command" << endl;
   cout << "               file_factory [src_file] [findstr] [ins_num] [grow]" << endl;
   cout << "               src_file is the source file, findstr is the string need to modify," << endl;
   cout << "               ins_num is the value of replacement, grow is every time the growth " << endl;
   cout << "               Note the number should be less than the length of the string to modify" << endl;
   cout << "               Digital replacement to findstr searches at the end" << endl;
   
   exit(0);
}


int main(int argc, char *argv[])
{   
    int     i_ret;
    int     i_opt; 
    int     i;
    
    char   *p_val_tmp;
    int     i_val_len_tmp;

    int     i_loop_num = 1;

    char   *p_file_src = NULL;
    char   *p_file_ins = NULL;
    int     fd_src;
    int     fd_ins;
    char   *p_buf_src;
    char   *p_buf_ins;
    int     i_len_src;
    int     i_len_ins;
    int     i_offset;  

    char   *find_str = "file_factory";
   
    if (argc != 4 && argc != 5) {
        printf("para num:%d is err!\n", argc);
        help_usage_en();
        return -1;
    }

    /* 插入值 */
    if (argc == 4) {
        p_file_src = argv[1];
        p_file_ins = argv[2];
        i_loop_num = (int)strtol(argv[3], NULL, 10);
        printf("src_file:%s ins_file:%s loop_num:%d\n", p_file_src, p_file_ins, i_loop_num);
        

        fd_src = open(p_file_src, O_RDWR);
        if (-1 == fd_src) {
            perror("open file err!");
            return -1;
        }

        /* 获取文件长度 */
        i_len_src = lseek(fd_src, 0, SEEK_END);
        lseek(fd_src, 0, SEEK_SET);
        printf("src_file len:%d\n", i_len_src);

        p_buf_src = (char *) malloc (sizeof(char) * i_len_src); 
        if (p_buf_src == NULL) {
            perror("malloc err");
            return -1;
        }

        if (-1 == read(fd_src, p_buf_src, i_len_src) ) {
            perror("read err");
            free(p_buf_src);
            return -1;
        }

        /* 查找字符串 */
        p_val_tmp = strstr(p_buf_src, find_str);
        if (p_val_tmp == NULL) {
            printf("find %s err!\n", find_str);
            free(p_buf_src);
            return -1;
        }

        /* 写入 */
        /* 获取写入字符串 */
        fd_ins = open(p_file_ins, O_RDONLY);
        if (-1 == fd_ins) {
            perror("open file err!");
            return -1;
        }

        /* 获取文件长度 */
        i_len_ins = lseek(fd_ins, 0, SEEK_END);
        lseek(fd_ins, 0, SEEK_SET);
        printf("ins_file len:%d\n", i_len_ins);

        p_buf_ins = (char *) malloc (sizeof(char) * i_len_ins); 
        if (p_buf_ins == NULL) {
            perror("malloc err");
            return -1;
        }

        if (-1 == read(fd_ins, p_buf_ins, i_len_ins) ) {
            perror("read err");
            free(p_buf_src);
            free(p_buf_ins);
            return -1;
        }

        /* 移动写指针到指定位置 */
        i_offset = p_val_tmp - p_buf_src;
        lseek(fd_src, i_offset, SEEK_SET);
        //printf("i_offset :%d\n", i_offset);
        for (i = 0; i < i_loop_num ; i++) {
            i_ret = write(fd_src, p_buf_ins, i_len_ins);
            if (i_ret == -1) {
                perror("write err!");
                free(p_buf_src);
                free(p_buf_ins);
                return -1;
            }
            i_offset += i_len_ins;
            //printf("i_offset :%d\n", i_offset);
            lseek(fd_src, i_offset, SEEK_SET);
        }

        /* 写入剩余字段 */
        i_ret = write(fd_src, p_val_tmp + strlen(find_str), 
            i_len_src - (p_val_tmp + strlen(find_str) - p_buf_src));
        if (i_ret == -1) {
            perror("write err!");
            free(p_buf_src);
            free(p_buf_ins);
            return -1;
        }
        free(p_buf_src);
        free(p_buf_ins);
        close(fd_src);
        close(fd_ins);
        printf("insert success!\n");
    } else {
        char *p_findstr;
        char *p_ins_str;
        int i_ins_num;
        int i_grow;
        char p_write_buf[10];

        p_file_src = argv[1];
        p_findstr = argv[2];
        p_ins_str = argv[3];
        i_ins_num = (int)strtol(p_ins_str, NULL, 10);
        i_grow = (int)strtol(argv[4], NULL, 10);
        if (strlen(p_findstr) < strlen(p_ins_str)) {
            printf("ins_num len err!\n");
            return -1;
        }
        printf("src_file:%s findstr:%s ins_num:%d grow:%d\n", p_file_src, p_findstr, i_ins_num, i_grow);

        fd_src = open(p_file_src, O_RDWR);
        if (-1 == fd_src) {
            perror("open file err!");
            return -1;
        }

        /* 获取文件长度 */
        i_len_src = lseek(fd_src, 0, SEEK_END);
        lseek(fd_src, 0, SEEK_SET);
        printf("src_file len:%d\n", i_len_src);

        p_buf_src = (char *) malloc (sizeof(char) * i_len_src); 
        if (p_buf_src == NULL) {
            perror("malloc err");
            return -1;
        }

        if (-1 == read(fd_src, p_buf_src, i_len_src) ) {
            perror("read err");
            free(p_buf_src);
            return -1;
        }

        p_val_tmp = strstr(p_buf_src, p_findstr);
        while (p_val_tmp != NULL) {
            memset(p_write_buf, 0, sizeof(p_write_buf));
            sprintf(p_write_buf, "%d", i_ins_num);
            
            i_offset = p_val_tmp + (strlen(p_findstr) - strlen(p_ins_str)) - p_buf_src;            
            
            lseek(fd_src, i_offset, SEEK_SET);
            
            i_ret = write(fd_src, p_write_buf, strlen(p_write_buf));
            if (i_ret == -1) {
                perror("write err!");
                free(p_buf_src);
                return -1;
            }

            i_ins_num += i_grow;
            p_val_tmp += strlen(p_findstr);
            p_val_tmp = strstr(p_val_tmp, p_findstr);
        }   

        free(p_buf_src);
        close(fd_src);
        printf("modification success!\n");
    }
    return 0;
}
