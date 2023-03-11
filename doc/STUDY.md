

# Redis源码解析

## RESP协议

mset a a b b

sds

```
*5
$4
mset
$1
a
$1
a
$1
b
$1
b
```



## SDS

```c
struct sdshdr {//hello
    long len;//当前字符串长度 
    long free;//剩余长度
    char buf[];//字符数组 "hello"->['h','e','l','l','o','\n']
};
```