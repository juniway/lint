// permu_combine.cpp
// 排列组合与回溯算法
递归 DFS

[前言] 这篇论文主要针对排列组合对回溯算法展开讨论，在每一个讨论之后，还有相关的推荐题。在开始之前，我们先应该看一下回溯算法的概念，所谓回溯：就是搜索一棵状态树的过程，这个过程类似于图的深度优先搜索（DFS），在搜索的每一步（这里的每一步对应搜索树的第i层）中产生一个正确的解，然后在以后的每一步搜索过程中，都检查其前一步的记录，并且它将有条件的选择以后的每一个搜索状态（即第i+1层的状态节点）。

需掌握的基本算法：

排列：就是从n个元素中同时取r个元素的排列，记做P(n,r)。（当r=n时，我们称P(n,n)=n!为全排列）例如我们有集合OR = {1,2,3,4},那么n = |OR| = 4,切规定r=3，那么P(4,3)就是：

{1,2,3}; {1,2,4}; {1,3,2}; {1,3,4};{1,4,2};{1,4,3};{2,1,3};{2,1,4}; {2,3,1}; {2,3,4}; {2,4,1}; {2,4,3}; {3,1,2}; {3,1,4}; {3,2,1}; {3,2,4}; {3,4,1}; {3,4,2}; {4,1,2}; {4,1,3}; {4,2,1}; {4,2,3}; {4,3,1}; {4,3,2}

算法如下：

int  n, r;
char used[MaxN];
int  p[MaxN];
 
void permute(int pos) {
  int i;
/*如果已是第r个元素了，则可打印r个元素的排列 */
    if (pos==r) {
        for (i=0; i<r; i++)
            cout << (p[i]+1);
        cout << endl;
        return;
    }
    for (i=0; i<n; i++)
        if (!used[i]) { /*如果第i个元素未用过*/
/*使用第i个元素，作上已用标记，目的是使以后该元素不可用*/
            used[i]++;
/*保存当前搜索到的第i个元素*/
            p[pos] = i;
/*递归搜索*/
           permute(pos+1);

/*恢复递归前的值，目的是使以后改元素可用*/
 used[i]--;
        }
}

相关问题
UVA 524 Prime Ring Problem



可重排列：就是从任意n个元素中，取r个可重复的元素的排列。例如，对于集合OR={1,1,2,2}, n = |OR| = 4, r = 2,那么排列如下：

{1,1}; {1,2}; {1,2}; {1,1}; {1,2}; {1,2}; {2,1}; {2,1}; {2,2}; {2,1}; {2,1}; {2,2}

则可重排列是：

{1,1}; {1,2}; {2,1}; {2,2}.

算法如下：

#define FREE -1
int n, r;
/*使元素有序*/
int E[MaxN] = {0,0,1,1,1};
int P[MaxN];
char used[MaxN];

void permute(int pos) {
int i;
/*如果已选了r个元素了，则打印它们*/
    if (pos==r)  {
        for (i=0; i<r; i++)
            cout << P[i];
        cout << endl;
        return;
    }
/*标记下我们排列中的以前的元素表明是不存在的*/
    P[pos] = FREE;
    for (i=0; i<n; i++)
/*如果第I个元素没有用过，并且与先前的不同*/
        if (!used[i] && E[i]!=P[pos]) {
/*使用这个元素*/
            used[i]++;
/*选择现在元素的位置*/
            P[pos] = E[i];
/*递归搜索*/
            permute(pos+1);
/*恢复递归前的值*/
            used[i]--;
        }
}

相关习题
UVA 10098 Generating Fast, Sorted Permutations



组合：从n个不同元素中取r个不重复的元素组成一个子集，而不考虑其元素的顺序，称为从n个中取r个的无重组合，例如OR = {1,2,3,4}, n = 4, r = 3则无重组合为：

{1,2,3}; {1,2,4}; {1,3,4}; {2,3,4}.

算法如下：

int n, r;
int C[5];
char used[5];
 
void combine(int pos, int h)
{
int i;
/*如果已选了r个元素了，则打印它们*/
    if (pos==r) {
        for (i=0; i<r; i++)
            cout<< C[i];
        cout<< endl;
        return;
    }
    for (i=h; i<=n-r+pos; i++) /*对于所有未用的元素*/
        if (!used[i]) {
/*把它放置在组合中*/
            C[pos] = i;
/*使用该元素*/
 used[i]++;
/*搜索第i+1个元素*/
     combine(pos+1,i+1);
/*恢复递归前的值*/
 used[i]--;
        }
}

相关问题：
Ural 1034 Queens in peaceful position

 

可重组合：类似于可重排列。

[例] 给出空间中给定n(n<10)个点，画一条简单路径，包括所有的点，使得路径最短。

解:这是一个旅行售货员问题TSP。这是一个NP问题，其实就是一个排列选取问题。

算法如下：

int  n, r;
char used[MaxN];
int  p[MaxN];
double min;
 
void permute(int pos, double dist)
{
int i;
    if (pos==n) {
        if (dist < min) min = dist;
        return;
    }
    for (i=0; i<n; i++)
        if (!used[i]) {
            used[i]++;
            p[pos] = i;
           if (dist + cost(point[p[pos-1]], point[p[pos]]) < min)
                permute(pos+1, dist + cost(point[p[pos-1]], point[p[pos]]));
 used[i]--;
        }
}

[例]对于0和1的所有排列，从中同时选取r个元素使得0和1的数量不同。

解 这道题很简单，其实就是从0到2^r的二元表示。

算法如下：

void dfs(int pos)
{
   if (pos == r)
   {
       for (i=0; i<r; i++) cout<<p[i];
       cout<<endl;
       return;
   }
   p[pos] = 0;
   dfs(pos+1);
   p[pos] = 1;
   dfs(pos+1);}

相关问题：

Ural

1005 Stone pile
1060 Flip Game
1152 The False Mirrors

 

[例]找最大团问题。

一个图的团，就是包括了图的所有点的子图，并且是连通的。也就是说，一个子图包含了n个顶点和n*(n-1)/2条边，找最大团问题是一个NP问题。算法如下：

#define MaxN 50
 
int  n, max;
int  path[MaxN][MaxN];
int  inClique[MaxN];
 
void dfs(int inGraph[])
{
int i, j;
int Graph[MaxN];
 
if ( inClique[0]+inGraph[0]<=max ) return;
if ( inClique[0]>max ) max=inClique[0];
 
/*对于图中的所有点*/
    for (i=1; i<=inGraph[0]; i++)
    {
/*把节点放置到团中*/
        ++inClique[0];
 inClique[inClique[0]]=inGraph[i];
/*生成一个新的子图*/
 Graph[0]=0;
 for (j=i+1; j<=inGraph[0]; j++)
     if (path[inGraph[i]][inGraph[j]] )
          Graph[++Graph[0]]=inGraph[j];
     dfs(Graph);
/*从团中删除节点*/
        --inClique[0];}
}
int main()
{
int inGraph[MaxN];
int i, j;
  cin >>n;
  while (n > 0)
  {
        for (i=0; i<n; i++)
 for (j=0; j<n; j++)
     cin >>path[i][j];
        max = 1;
/*初始化*/
        inClique[0]= 0;
        inGraph[0] = n;
 for (i=0; i<n; i++) inGraph[i+1]=i;
        dfs(inGraph);
        cout<<max<<endl;
        cin >>n;
  }
  return 0;}

 

 参考论文 <A fast algorithm for the maximum clique problem>

相关问题：

acm.zju.edu.cn: 1492 maximum clique

 

相关网站

http://acm.uva.es/p

http://acm.timus.ru/

 

Contact me:

MSN: Bing0672@Hotmail.com

/////////////////////////

  求集合子集，和全排列的递归算法实现(c++,Dev C++调试通过)


求集合全排列算法实现:

求集合所有子集的算法实现:

1.求集合全排列算法实现:

/*
  Name:
  Copyright:
  Author: XuLei
  Date: 01-11-05 09:40
  Description:求一个字符串集合(List)的全排列，一共有n!种(假设字符数为n)
  Algorithms:令E= {e1 , ..., en }表示n 个元素的集合，我们的目标是生成该集合的所有排列方式。令Ei
             为E中移去元素i 以后所获得的集合，perm (X) 表示集合X 中元素的排列方式，ei.p e r m
             (X)表示在perm (X) 中的每个排列方式的前面均加上ei 以后所得到的排列方式。例如，如果
             E={a, b, c}，那么E1={b, c}，perm (E1 )=( b c, c b)，e1 .perm(E1) = (a b c, a c b)。
             对于递归的基本部分，采用n = 1。当只有一个元素时，只可能产生一种排列方式，所以
             perm (E) = (e)，其中e 是E 中的唯一元素。当n > 1时，perm (E) = e1 .perm(E1) +e2 .p e r m
             (E2) +e3.perm(E3) + ... +en .perm (En)。这种递归定义形式是采用n 个perm(X) 来定义perm(E),
             其中每个X 包含n-1个元素。至此，一个完整的递归定义所需要的基本部分和递归部分都已完成。
*/
#include <iostream>
using namespace std;
//const int ListLength=10;
const int ListLength=3;     //字符串数组的长度
void Swap(char &c, char &s) //交换字符c和s
{
     char temp=c;
     c=s;
     s=temp;
}
void Perm(char *List, int m, int k)
{
     static int count=0;
     if(m==k)
     {
             cout<<++count<<":";
             for(int i=0; i<=ListLength-1; i++)
             {
                     cout<<List[i];
             }            
             cout<<endl;
     }
     else
     {
         for(int i=m; i<=k; i++)
         {
                  Swap(List[m],List[i]);
                  Perm(List, m+1, k);
                  Swap(List[m],List[i]);
                 
         }        
     }
        
}
int main()
{
    //char List[ListLength]={'a','b','c','d','e','f','g','h','i','j'};
    char List[ListLength]={'a','b','c'};
    Perm(List, 0, ListLength-1);
    system("pause");
    return 0; 

}

2. 求集合所有子集的算法实现:

/*
  Name:
  Copyright:
  Author: XuLei
  Date: 01-11-05 11:34
  Description: 求一个集合(List)的所有子集，并输出
  Algorithms: 由SubSet函数来求所有的子集，SubSet(char *List, int m, char *Buffer, int flag)
              基本思想为首先取出List[m],然后依次把List[m+1...ListLength-1]加到List[m]后面，
              每加一个，存储在集合Buffer[]中,并输出。由flag标识数组Buffer的长度。
              以集合{a,b,c}为例，首先取出a存入Buffer[0],输出。
                                 然后调用SubSet(char *List, 1, char *Buffer, 1)把Buffer[1]=b
                                    输出ab。
                                 再调用SubSet(char *List, 2, char *Buffer, 2) 把Buffer[2]=c
                                    输出abc。
                                 再进入SubSet(char *List, 1, char *Buffer, 1) 把Buffer[1]=c
                                    输出ac。
                                 退回最外层的循环。
                                 取出b存入Buffer[0],输出。
                                 然后调用SubSet(char *List, 1, char *Buffer, 1)把Buffer[1]=c
                                    输出bc。
                                 取出c存入Buffer[0],输出。               
*/
#include <iostream>
using namespace std;
const int ListLength=10;
//const int ListLength=3;

//输出Buffer集合
void Output(char *Buffer, int flag)
{
     static int count=1;
     if(count==1)
     {
              cout<<count++<<": { }"<<endl;        
     }
     cout<<count++<<": {";
     for(int i=0; i<=flag; i++)
     {
              cout<<Buffer[i];            
     }
     cout<<"}"<<endl;
}
//找到元素c在集合List中的位置
int Index(char *List, char c)
{
     for(int i=0; i<=ListLength-1; i++)
     {
              if(c==List[i])
              {
                    return i;            
                    break;
              }                 
     }
     return -1;    
}

void SubSet(char *List, int m, char *Buffer, int flag) {    
     if(m <= ListLength-1) {
          /*if(m==0)
          {
                  Buffer[0]=List[0];
          }*/
          //Buffer[flag]=List[m];
          /*if(flag==0)
          {
                Buffer[flag]=List[m];
          }*/
         
          for(int i=(flag==0) ? 0 : Index(List,Buffer[flag-1])+1; i<=ListLength-1; i++)
          //当flag==0时，Buffer中没有任何元素，此时i=[0...ListLength-1]
          //当flag>0时，找到Buffer中的最后一个元素在集合List中的位置i，把[i....ListLength-1]
          //处的元素，加到Buffer元素的最后面
          {
                Buffer[flag]=List[i];               
                Output(Buffer,flag);
                SubSet(List, m+1, Buffer,flag+1);
          }         
     }
     return;
}

int main() {
    char List[ListLength]={'a','b','c','d','e','f','g','h','i','j'};  
    //char List[ListLength]={'a','b','c'};
    char Buffer[ListLength]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
    //char Buffer[ListLength]={' ',' ',' '};
    //int flag=0;
    //TEST
    //cout<<Index(List,'c');  OK
    SubSet(List,0,Buffer,0);
    system("pause");
    return 0;  
}