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
 �� �� ��  : test_copy
 ��������  : �������캯������
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 �ܽ�      : �������캯����ʵ�������ֵ���ݺ����ô��ݣ���ע��ǳ���������������ָ��
             ������£�����д�������캯��
 
 �޸���ʷ      :
  1.��    ��   : 2016��6��6��
    ��    ��   : zj
    �޸�����   : �����ɺ���

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
