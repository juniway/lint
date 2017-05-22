
#[经典题] 子数组的最大乘积

给定一个长度为N的整数数组，只允许用乘法，不能用除法，计算任意（N-1）个数的组合乘积中的最大的一组，并写出算法的时间复杂度。


#### 分析

思路一 穷举法
我们把所有可能的（N-1）个数的组合找出来，分别计算它们的乘积，并比较大小。由于总共有N个（N-1）个数的组合，总的时间复杂度为O(N^2),但显然这不是最好的思路。

思路二 空间换时间
计算（N-1）个数的组合乘积，假设第i个（`0<=i<=N-1`）元素被排除在乘积之外（如下图）。
![](http://img.blog.csdn.net/20150215153255802)

设 num[] 为初始数组 
Left[i] 表示前 i 个元素（包括第 i 个元素）的乘积（`0 <= i <= N-1`） 

    Left[i] = Left[i-1] * num[i] 

Right[i] 表示后 N-i 个元素（包括第 i 个元素）的乘积（`0 <= i <= N-1`） 

    Right[i] = Right[i+1] * num[i]

设 p[i] 为数组除第 i 个元素外，其他 N-1 个元素的乘积： 

    P[i] = Left[i-1] * Right[i+1]

举个例子：
![](http://img.blog.csdn.net/20150215153347532)

    P[4] = Left[3] * Right[5] = a1 * a2 * a3 * a4 * a6 * a7 * a8 * a9 * a10

由于只需要从头到尾，从尾到头扫描两次即可得到数组 Left[] 和 Right[],从而线性时间得到 P[i]。所以很容易的就可以得到最大值（只需遍历一次p数组）。总的时间复杂度为计算数组 Left[], Right[], p[]的时间复杂度加上查找 p[] 最大值的时间复杂度即 O(N) 。

思路三

通过分析，进一步减少计算量。假设N个数的乘积为P，针对P的正负性进行如下分析： 
（1）P为0 
那么，数组中至少包含一个0。假设除去一个0之外，其他N-1个数的乘积为Q，根据Q的正负性进行讨论： 
Q为0，说明数组中至少有两个0，那么N-1个数的乘积只能为0。 
Q为正，返回Q。因为如果用0替换剩余N-1个数中的任意一个，所得乘积结果都为0，小于之前的Q，因此乘积最大值为Q。 
Q为负，返回0。因为如果用0替换剩余N-1个数中的任意一个，所得结乘积果都为0，大于之前的Q，因此乘积最大值为0。 
（2）P为负 
根据“负负得正”的乘法性质，自然想到的是从N个整数中去掉一个负数，使得N-1个数乘积为正数。而要使这个整数最大，这个被去掉的负数绝对值必须是数组中最小的。我们只需要扫描一遍数组，把绝对值最小的负数去掉就可以了。 
（3）P为正 
类似P为负的情况，应该去掉一个绝对值最小的正数值，这样得到的N-1个数乘积就是最大的。

上面的思路采用了直接求N个数的乘积P，进而判断P的正负性的办法，但是直接求乘积往往有溢出的危险，事实上可做一个小的转变，不需要直接乘积，而是求出数组中正数，负数和0的个数，从而判断P的正负性。

在时间复杂度上，由于只需要一次遍历数组，在遍历数组的同时就可得到数组中正数，负数和0的个数，以及数组中绝对值最小的正数和负数，时间复杂度为O(N)

##### Solutions

解法二

```cpp
#include <iostream>
#include <cstring>
using namespace std;

class Solution {
public:
    double MaxProduct(double num[],int n){
        if(n <= 0){
            return 0;
        }//if
        double max = num[0],p;
        double Left[n],Right[n];
        // 初始化
        Left[0] = num[0];
        Right[n-1] = num[n-1];
        // 计算Left数组
        for(int i = 1;i < n;++i){
            Left[i] = Left[i-1] * num[i];
        }//for
        // 计算Right数组
        for(int i = n-2;i >= 0;--i){
            Right[i] = Right[i+1] * num[i];
        }//for
        // max
        int left,right;
        for(int i = 0;i < n;++i){
            left = (i - 1) >= 0 ? Left[i-1] : 1;
            right = (i + 1) < n ? Right[i+1] : 1;
            p = left * right;
            if(p > max){
                max = p;
            }//if
        }//for
        return max;
    }
};

int main() {
    Solution solution;
    double num[] = {-2.5,-4,0.5,3,1,2,-3};
    cout<<solution.MaxProduct(num,7)<<endl;
}
```

解法三

```cpp
#include <iostream>
#include <climits>
#include <cmath>
using namespace std;

class Solution {
public:
    double MaxProduct(double num[],int n){
        if(n <= 0){
            return 0;
        }
        // 绝对值最小的负数,绝对值最小的正数
        double pMin = INT_MAX,nMin = INT_MAX;
        // 绝对值最小的负数,绝对值最小的正数,0的下标
        int pIndex = 0,nIndex = 0,zeroIndex;
        // 0,正数,负数个数
        int zCount = 0,pCount = 0,nCount = 0;
        // 去除掉元素的下标
        int index = 0;
        // 统计
        for(int i = 0;i < n;++i){
            if(num[i] == 0){
                zeroIndex = i;
                ++zCount;
            }//if
            else if(num[i] > 0){
                ++pCount;
                // 绝对值最小的正数
                if(num[i] < pMin){
                    pIndex = i;
                    pMin = num[i];
                }//if
            }//else
            else{
                ++nCount;
                // 绝对值最小的负数
                if(fabs(num[i]) < nMin){
                    nMin = fabs(num[i]);
                    nIndex = i;
                }//if
            }//else
        }
        if(zCount > 0){ // P为0
            // Q为0
            if(zCount - 1 > 0){
                return 0;
            }//if
            // Q为负
            if(nCount % 2){
                return 0;
            }//if
            // Q为正
            else{
                // 去掉下标为zeroIndex的元素
                index = zeroIndex;
            }//else
        }//if
        // P为正去掉绝对值最小的正数
        else if(nCount % 2 == 0){
            index = pIndex;
        }
        // P为负去掉绝对值最小的负数
        else{
            index = nIndex;
        }//else
        // 最大乘积
        double max = 1;
        for(int i = 0;i < n;++i){
            if(i != index){
                max *= num[i];
            }//if
        }//for
        return max;
    }
};


int main() {
    Solution solution;
    double num[] = {2.5,4,-0.5,3,-1,2,3};
    cout<<solution.MaxProduct(num,7)<<endl;
}
```