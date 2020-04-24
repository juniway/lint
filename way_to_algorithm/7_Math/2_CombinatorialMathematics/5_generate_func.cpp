/*
 *本部分介绍使用母函数方法实现数的拆分问题求解
 *数的拆分问题描述如下：
 *（不允许重复，比如1+3和3+1只能算一种）
 *2=1+1 所以2有两种
 *3=1+2=1+1+1 所以3的拆分有3种
 *4=1+3=1+1+2=1+1+1+1=2+2 所以4有5种
 *以此类推可以计算出更大的数的拆分种类
 *
 *
 *我们假设要求的数是N（N>=1,且为正整数）
 *
 *那么比N小的数都是有可能组成大数N的
 *共有1,2,3,4,5,6,7,8,9,10,....N-1,N
 *
 *设每个比N小的数为I，且I为无限个，那么出现相同的I也不会超过N个
 *对于每个I，能组成的数有
 *个数 0 	1 	2	3	4	5 	6 	7 	 ....	N-1		N
 *数字 0 	I 	2*I	3*I	4*I	5*I	6*I 7*I	 ....	I*(N-1) I*N
 *考虑到I也是从1-N变化的，不同之间的I也是可以组合的
 *
 *比如
 *个数 0 	1 	2	3	4	5 	6 	7 	 ....	N-1		N
 *数字 0 	J 	2*J	3*J	4*J	5*I	6*J 7*J	 ....	J*(N-1) J*N
 *由K个I和S个J组成的数字必然和为I+J,且有K*S种组法
 *这就迫使我们构造母函数
 *F(X,I)=X^(I*0)+X^(I*1)+X^(I*2)+X^(I*3)+X^(I*4)+....+X^(I*N)
 *其中1<=I<=N
 *我们将F(X,1)*F(X,2)*F(X,3)*F(X,4)*****F(X,N-1)*F(X,N)
 *得到的系数就是对应指数的方案数了
 *
 *
 *
 *
 *本程序也就是实现这样一个功能，快速计算数分解的可能数。
 */

#include <iostream>
#include <string.h>
#include <stdio.h>

#include "com_local.h"
#include "general_head.h"
using namespace std;

const int N=10005;

int c1[N],c2[N];

void calculus_number_diverse(int argc,char** argv)
{
    int n,i,j,k;
    while(cin>>n&&n)
    {
        if(n==0) break;
        for(i=0;i<=n;i++) /*需要交换数字作为辅助*/
        {
            c1[i]=1;
            c2[i]=0;
        }
        for(i=2;i<=n;i++) /*I*/
        {
            for(j=0;j<=n;j++) /*每两个式子相乘*/
                for(k=0;k+j<=n;k+=i) /*为了提高计算速度，减少不必要计算，将指数大于N的不算了*/
                    c2[k+j]+=c1[j];
            for(j=0;j<=n;j++)
            {
                c1[j]=c2[j];
                c2[j]=0;
            }
        }
        cout<<c1[n]<<endl;
    }
}
