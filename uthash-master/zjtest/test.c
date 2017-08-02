#include "uthash.h"
#include <stdlib.h>   /* malloc */
#include <stdio.h>    /* printf */


struct my_struct {
    int ikey;                    /* key */
    int value;
    UT_hash_handle hh;         
};
 
struct my_struct *g_users = NULL;

//ʵ���Լ��Ĳ��ҽӿں�����
struct my_struct *find_user(int ikey) {
    struct my_struct *s;
    HASH_FIND_INT(g_users, &ikey, s );
    return s;
}

//ʵ���Լ��Ĳ���ӿں�����
void add_user(int ikey, int value) {
    struct my_struct *s;
    HASH_FIND_INT(g_users, &ikey, s);  /* ����ǰ�Ȳ鿴keyֵ�Ƿ��Ѿ���hash��g_users������ */
    if (s==NULL) {
      s = (struct my_struct*)malloc(sizeof(struct my_struct));
      s->ikey = ikey;
      HASH_ADD_INT(g_users, ikey, s );  /* ���������ȷ���߲��뺯�����Լ������hash�ṹ���м����������� */
    }
    s-> value = value;
}
//ʵ��ɾ���ӿ�
void delete_user(int ikey) {
    struct my_struct *s = NULL;
    HASH_FIND_INT(g_users, &ikey, s);
    if (s!=NULL) {
      HASH_DEL(g_users, s); 
      free(s);            
    }
}
//���hash��
void delete_all() {
    struct my_struct *current_user, *tmp;
 
    HASH_ITER(hh, g_users, current_user, tmp) {
        HASH_DEL(g_users,current_user);  
        free(current_user);            
    }
}

int main(int argc,char *argv[])
{
    int i;
    struct my_struct *user, *current_user, *tmp;

    /* create elements */
    for(i=0; i<10000000; i++) {
        user = (struct my_struct*)malloc(sizeof(struct my_struct));
        if (user == NULL) {
            exit(-1);
        }
        user->ikey = i;
        user->value = i*i;
        HASH_ADD_INT(g_users, ikey, user);
    }
	
	unsigned int num_users;
    num_users = HASH_COUNT(g_users);
    printf("there are %u items, bloom_sig:%d\n", num_users, g_users->hh.tbl->nonideal_items);
	
	HASH_ITER(hh, g_users, current_user, tmp) {
        //printf("user_key:%d, value:%d\n", current_user->ikey, current_user->value);     
    }	
 
    HASH_ITER(hh, g_users, current_user, tmp) {
        HASH_DEL(g_users,current_user);  
        free(current_user);            
    }

    num_users = HASH_COUNT(g_users);
    printf("there are %u items\n", num_users);
	
    return 0;
}
