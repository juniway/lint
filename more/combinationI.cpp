// http://blog.163.com/he3_2001/blog/static/1743928520114891457258/
最近一直在考虑从m个数里面取n个数的算法。最容易理解的就是递归，
但是其效率很低。一直找寻中，今日得果。

全排列算法   
    
  从1到N，输出全排列，共N！条。   
  分析：用N进制的方法吧。设一个N个单元的数组，对第一个单元做加一操作，满N进   
  一。每加一次一就判断一下各位数组单元有无重复，有则再转回去做加一操作，没   
  有则说明得到了一个排列方案。
 //////////////////////////////////////////////////////

递归算法
    全排列是将一组数按一定顺序进行排列，如果这组数有n个，那么全排列数为n!个。现以{1, 2, 3, 4, 5}为
例说明如何编写全排列的递归算法。

1、首先看最后两个数4, 5。 它们的全排列为4 5和5 4, 即以4开头的5的全排列和以5开头的4的全排列。
由于一个数的全排列就是其本身，从而得到以上结果。
2、再看后三个数3, 4, 5。它们的全排列为3 4 5、3 5 4、 4 3 5、 4 5 3、 5 3 4、 5 4 3 六组数。
即以3开头的和4,5的全排列的组合、以4开头的和3,5的全排列的组合和以5开头的和3,4的全排列的组合.
从而可以推断，设一组数p = {r1, r2, r3, ... ,rn}, 全排列为perm(p)，pn = p - {rn}。
因此perm(p) = r1perm(p1), r2perm(p2), r3perm(p3), ... , rnperm(pn)。当n = 1时perm(p} = r1。
为了更容易理解，将整组数中的所有的数分别与第一个数交换，这样就总是在处理后n-1个数的全排列。

算法如下：
#include <stdio.h>  
int n = 0;  
void perm(int list[], int k, int m){
    int i;
    if(k >= m){ // STOP! find all
        for(i = 0; i <= m; i++)
            printf("%d ", list[i]);
        printf("\n");
        n++;
    }
    else{    
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
    printf("total:%d\n", n);
    return 0; 
}  

全排列
设R={r1,r2,...,rn}是要进行排列的n个元素，Ri = R-{ri}. 集合 X 中元素的全排列记为Perm(X)。
(ri)Perm(X)表示在全排列Perm(X)的每一个排列上加前缀ri得到的排列。

R的全排列可归纳定义如下：
当 n = 1 时， Perm(R) = (r),其中r 是集合R中唯一的元素；
当 n >1 时， Perm(R)有 (r1)Perm(R1),(r2)Perm(R2),.......,(rn)Perm(Rn)构成

依此递归定义，可设计产生Perm(R)的递归算法如下：
template <class Type>
void Perm(Type list[], int k, int m){
    if(k == m){
        for(int i = 0; i <= m; ++i)
            cout << list[i];
        cout << endl;
    }
    else{
        for(int i = k; i <= m; ++i){
            swap(list[k], list[i]);
            Perm(list, k + 1, m);
            swap(list[k], list[i]);
         }
    }
}
