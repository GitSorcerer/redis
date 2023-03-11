#include <stdio.h>
#include <stdarg.h>
typedef char *mysds;

struct mysdshdr {
    long len;
    long free;
    char buf[];
};


struct mysdshdr sh ={6,2,{'h','e','l','l','o'}};

//作用与系统提供的snprintf()函数相同
int my_snsprintf(char *s,int size,const char *fmt, ...){
    va_list ap;
    int n=0;
    va_start (ap,fmt);
    n=vsnprintf(s,size,fmt,ap);
    va_end(ap);
    return n;
}

//执行 gcc -o sds_test sds_test.c  
int main () {
    struct  mysdshdr *s =&sh;
    printf("%d\n",sizeof(struct mysdshdr));
    printf("%d\n",sizeof(long));
    printf("%d, %p\n",s->len,&(s->len));
    printf("%d, %p\n",s->free,&(s->free));
    printf("%s, %p\n",s->buf,&(s->buf));

    mysds sd=s->buf;//字符串数组地址
    printf("%s\n",sd);
    //获取sdshdr的地址  sdshdr总共占用16个字节(2个long) 所以根据buf可以获取到sds的地址
    struct mysdshdr *new_sh=(void *)(sd-(sizeof(struct mysdshdr)));
    printf("当前字符串长度:%d,剩余字符串长度:%d\n",new_sh->len,new_sh->free);
    char str[1024];
    my_snsprintf(str,sizeof(str),"%d,%d,%d,%d\n",5,6,7,8);
    printf("%s\n",str);

    return 0;
}