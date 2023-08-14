/*
 * @Author: gaoh
 * @Date: 2023-08-12 15:39:11
 * @LastEditTime: 2023-08-12 17:41:07
 */
#include <stdio.h>
#include "../zipmap.c"
#include "../zmalloc.c"

int main(){
    unsigned char *zm;

    zm = zipmapNew();

    zm = zipmapSet(zm,(unsigned char*) "name",4, (unsigned char*) "foo",3,NULL);
    zm = zipmapSet(zm,(unsigned char*) "surname",7, (unsigned char*) "foo",3,NULL);
    zm = zipmapSet(zm,(unsigned char*) "age",3, (unsigned char*) "foo",3,NULL);
    zipmapRepr(zm);
    //{status 0}{key 4}name{value 3}foo{key 7}surname{value 3}foo{key 3}age{value 3}foo{end}
    // exit(1);

    zm = zipmapSet(zm,(unsigned char*) "hello",5, (unsigned char*) "world!",6,NULL);
    zm = zipmapSet(zm,(unsigned char*) "foo",3, (unsigned char*) "bar",3,NULL);
    zm = zipmapSet(zm,(unsigned char*) "foo",3, (unsigned char*) "!",1,NULL);
    zipmapRepr(zm);
    //{status 0}{key 4}name{value 3}foo{key 7}surname{value 3}foo{key 3}age{value 3}foo{key 5}hello{value 6}world!{key 3}foo{value 1}![..]{end}
    zm = zipmapSet(zm,(unsigned char*) "foo",3, (unsigned char*) "12345",5,NULL);
    zipmapRepr(zm);
    //{status 1}{key 4}name{value 3}foo{key 7}surname{value 3}foo{key 3}age{value 3}foo{key 5}hello{value 6}world!{9 empty block}{key 3}foo{value 5}12345{end}
    zm = zipmapSet(zm,(unsigned char*) "new",3, (unsigned char*) "xx",2,NULL);
    zm = zipmapSet(zm,(unsigned char*) "noval",5, (unsigned char*) "",0,NULL);
    zipmapRepr(zm);
    //{status 1}{key 4}name{value 3}foo{key 7}surname{value 3}foo{key 3}age{value 3}foo{key 5}hello{value 6}world!{key 3}new{value 2}xx[.]{key 3}foo{value 5}12345{key 5}noval{value 0}{end}
    zm = zipmapDel(zm,(unsigned char*) "new",3,NULL);
    zipmapRepr(zm);
    //{status 1}{key 4}name{value 3}foo{key 7}surname{value 3}foo{key 3}age{value 3}foo{key 5}hello{value 6}world!{9 empty block}{key 3}foo{value 5}12345{key 5}noval{value 0}{end}
    printf("\nPerform a direct lookup:\n");
    {
        unsigned char *value;
        unsigned int vlen;

        if (zipmapGet(zm,(unsigned char*) "foo",3,&value,&vlen)) {
            printf("  foo is associated to the %d bytes value: %.*s\n",
                vlen, vlen, value);
        }
    }
    printf("\nIterate trought elements:\n");
    {
        unsigned char *i = zipmapRewind(zm);
        unsigned char *key, *value;
        unsigned int klen, vlen;

        while((i = zipmapNext(i,&key,&klen,&value,&vlen)) != NULL) {
            printf("  %d:%.*s => %d:%.*s\n", klen, klen, key, vlen, vlen, value);
        }
    }
    return 0;


}