#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <signal.h>
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

static void test_usage(void)
{
   cout << "usage: cxx_test [-hd]                            " << endl;
   cout << "       -h                    print help messages" << endl;
   cout << "       -d                    big lit duan check" << endl;
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

class Point
{
    public:
        Point(int xx = 0, int yy = 0) {
            X = xx;
            Y = yy;
        }

        Point(Point &p);

        int getX() {
            return X;
        }

        int getY() {
            return Y;
        }

        void setX(int xx) {
            X = xx;
        }

        void setY(int yy) {
            Y = yy;
        }
    private:
        int X, Y;
};

Point::Point(Point &p) {
    X = p.X;
    Y = p.Y;
    cout << "copy called!!" << endl;
}

void copy_fun1(Point p)
{
    cout << "fun1:" << p.getX() << endl;
    p.setX(8);
    cout << "fun1:" << p.getX() << endl;
}

Point copy_fun2()
{
    Point C(3, 2);
    cout << "fun2:" << C.getX() << endl;
    return C;
}


/*****************************************************************************
 函 数 名  : test_copy
 功能描述  : 拷贝构造函数测试
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 总结      : 拷贝构造函数其实就是类的值传递和引用传递，需注意浅拷贝和深拷贝，即有指针
             的情况下，需重写拷贝构造函数
 
 修改历史      :
  1.日    期   : 2016年6月6日
    作    者   : zj
    修改内容   : 新生成函数

*****************************************************************************/
void test_copy( void )
{
    Point A(4, 5);
    Point B(A);
    cout << B.getX() << endl;
    copy_fun1(B);
    cout << B.getX() << endl;

    Point D;
    D = copy_fun2();
    cout << D.getX() << endl;
}

int main(int argc,char *argv[])
{   
    //test_copy();
}
