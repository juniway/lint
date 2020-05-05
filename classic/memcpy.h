// 1. 不能对 void 指针进行算法操作，比如 p++ 这样的操作，所以需要转换为具体的类型指针来操作，例如 char *
// 2. 需要考虑地址重叠的情况，也即:
//   1) dst > src && dst < src + src_length
// dest 处于 src 和 src+n 之间时，一定会出现内存覆盖的现象，而且还会改变源字符串的内容，进行错误的拷贝。

//   2) dst < src && dst + src_len < src

// 注意：
// 标准库也提供了地址重叠时的内存拷贝函数：memmove()，那么为什么还要考虑重写 memcpy() 函数呢?
// 因为 memmove() 函数的实现效率问题
// 该函数把源字符串拷贝到临时 buf 里，然后再从临时 buf 里写到目的地址，增加了一次不必要的开销。

// 已知 memcpy 的函数原型为： void* memcpy(void *dst , const void* src , size_t count)

#include <iostream>
using namespace std;

void *memcpy(void *dst, void *src, size_t n) {
    // fault tolerant
    if (dst == NULL || src == NULL){
        return NULL;
    }

    unsigned char *pdst = (unsigned char *)dst;
    unsigned char *psrc = (unsigned char *)src;

    // if address overlap
    bool flag1 = pdst >= psrc && pdst < psrc + n;
    bool flag2 = pdst < pscr && pdst + n >= psrc;

    if (flag2) {
        pdst = pdst + n - 1

        psrc = psrc + n - 1

        // copy reversely
        while(n--) {
            *(pdst+n-1)-- = *(psrc+n-1)--;
        }
    }

    // not overlap
    while(n--) {
        *pdst = *psrc;
        pdst++;
        psrc++;
    }

    return dst;

}
