// http://blog.163.com/he3_2001/blog/static/1743928520114891457258/
最近一直在考虑从 m 个数里面取 n 个数的算法。最容易理解的就是递归，
但是其效率很低。一直找寻中，今日得果。

全排列算法

  从 1 到 N ，输出全排列，共 N！条。
  分析：用 N 进制的方法吧。设一个 N 个单元的数组，对第一个单元做加一操作，满 N 进 一。
  每加一次一就判断一下各位数组单元有无重复，有则再转回去做加一操作，没有则说明得到了一个排列方案。
 //////////////////////////////////////////////////////

递归算法
    全排列是将一组数按一定顺序进行排列，如果这组数有 n 个，那么全排列数为 n! 个。现以 {1, 2, 3, 4, 5} 为例说明如何编写全排列的递归算法。

1、首先看最后两个数 4, 5。它们的全排列为 4 5 和 5 4, 即以 4 开头的 5 的全排列和以 5 开头的 4 的全排列。由于一个数的全排列就是其本身，从而得到以上结果。
2、再看后三个数 3, 4, 5。它们的全排列为 3 4 5、3 5 4、 4 3 5、 4 5 3、 5 3 4、 5 4 3 六组数。
即以 3 开头的和 4, 5 的全排列的组合、以 4 开头的和 3, 5 的全排列的组合和以 5 开头的和 3, 4 的全排列的组合.

从而可以推断，设一组数p = {r1, r2, r3, ... , rn}, 全排列为 perm(p)，pn = p - {rn}。
因此 perm(p) = r1perm(p1), r2perm(p2), r3perm(p3), ... , rnperm(pn)。
当 n = 1 时 perm(p) = r1。

算法核心原理：
全排列 perm(p) 由每一个数，与剩下其他的数的全排列构成。
具体实现方式就是，将整组数中的所有的数分别与第一个数交换，然后递归求剩余数的全排列，这样就总是在处理后 n-1 个数的全排列。处理完之后记得交换回来。

算法如下：

#include <stdio.h>
int n = 0;
void perm(int list[], int k, int m) {
    int i;
    if(k >= m){ // STOP! find all
        for(i = 0; i <= m; i++)
            printf("%d ", list[i]);
        printf("\n");
        n++;
    } else{
        for(i = k; i <= m; i++){
            swap(&list[k], &list[i]);
            perm(list, k + 1, m);
            swap(&list[k], &list[i]);
        }
    }
}

int main(){
    int list[] = {1, 2, 3, 4, 5};
    perm(list, 0, 4);
    printf("Total: %d\n", n);
    return 0;
}

全排列
设 R = {r1, r2, ..., rn} 是要进行排列的 n 个元素，Ri = R - {ri}. 集合 X 中元素的全排列记为 Perm(X)。
(ri)Perm(X) 表示在全排列 Perm(X) 的每一个排列上加前缀 ri 得到的排列。

R 的全排列可归纳定义如下：
当 n = 1 时， Perm(R) = (r), 其中 r 是集合 R 中唯一的元素；
当 n > 1 时， Perm(R) 由 (r1)Perm(R1), (r2)Perm(R2), ......, (rn)Perm(Rn) 构成

依此递归定义，可设计产生 Perm(R) 的递归算法如下：

template <class Type>
void Perm(Type list[], int k, int m){
    if(k == m){
        for(int i = 0; i <= m; ++i)
            cout << list[i];
        cout << endl;
    } else{
        for(int i = k; i <= m; ++i){
            swap(list[k], list[i]);
            Perm(list, k + 1, m);
            swap(list[k], list[i]);
         }
    }
}
