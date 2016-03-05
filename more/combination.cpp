// combination.cpp
尽管排列组合是生活中经常遇到的问题，可在程序设计时，不深入思考或者经验不足都让人无从下手。
由于排列组合问题总是先取组合再排列，并且单纯的排列问题相对简单，
所以本文仅对组合问题的实现进行详细讨论。

组合算法   
  本程序的思路是开一个数组，其下标表示1到m个数，数组元素的值为1表示其下标   
  代表的数被选中，为0则没选中。     
  首先初始化，将数组前n个元素置1，表示第一个组合为前n个数。     
  然后从左到右扫描数组元素值的“10”组合，找到第一个“10”组合后将其变为   
  “01”组合，同时将其左边的所有“1”全部移动到数组的最左端。     
  当第一个“1”移动到数组的m-n的位置，即n个“1”全部移动到最右端时，就得   
  到了最后一个组合。     
  例如求5中选3的组合：     
  1   1   1   0   0   //1,2,3     
  1   1   0   1   0   //1,2,4     
  1   0   1   1   0   //1,3,4     
  0   1   1   1   0   //2,3,4     
  1   1   0   0   1   //1,2,5     
  1   0   1   0   1   //1,3,5     
  0   1   1   0   1   //2,3,5     
  1   0   0   1   1   //1,4,5     
  0   1   0   1   1   //2,4,5     
  0   0   1   1   1   //3,4,5

以在n个数中选取m(0 < m <= n)个数为例，问题可分解为：
1. 首先从n个数中选取编号最大的数，然后在剩下的n-1个数里面选取m-1个数，
直到从n-(m-1)个数中选取1个数为止。
2. 从n个数中选取编号次小的一个数，继续执行1步，直到当前可选编号最大的数为m。
很明显，上述方法是一个递归的过程，也就是说用递归的方法可以很干净利索地求得所有组合。
下面是递归方法的实现：
/// 求从数组a[1..n]中任选m个元素的所有组合。
/// a[1..n]表示候选集，m表示一个组合的元素个数。
/// b[1..M]用来存储当前组合中的元素, 常量M表示一个组合中元素的个数。
void combine(int a[], int n, int m,  int b[], const int M){ 
    for(int i = n; i >= m; i--){  // 注意这里的循环范围
        b[m-1] = i - 1;
        if (m > 1) combine(a, i-1, m-1, b, M);
        else{   // m == 1, 输出一个组合
            for(int j=M-1; j>=0; j--) cout << a[b[j]] << " ";
            cout << endl;
        }
    }
}

因为递归程序均可以通过引入栈，用回溯转化为相应的非递归程序，
所以组合问题又可以用回溯的方法来解决。
为了便于理解，我们可以把组合问题化归为图的路径遍历问题，
在n个数中选取m个数的所有组合，相当于在一个这样的图中（下面以从1,2,3,4中任选3个数为例说明）
求从[1, 1]位置出发到达[m, x] (m <= x <= n) 位置的所有路径：
1   2   3   4
    2   3   4
        3   4
            4

上图是截取n×n右上对角矩阵的m行构成，我们要求的所有组合就相当于从第一行的第一列元素[1,1]出发，
到第三行的任意一列元素作为结束的所有路径，规定每走一步需跨越一行，
并且从上一行的任何一个元素到其下一行中列处于其右面的任何一个元素均有一路径相连，
显然任一路径经过的数字序列就对应一个符合要求的组合。
下面是非递归的回溯方法的实现：
/// 求从数组a[1..n]中任选m个元素的所有组合。
/// a[1..n]表示候选集，m表示一个组合的元素个数。
/// 返回所有排列的总数。
int combine(int a[], int n, int m){  
    m = m > n ? n : m;

    int* order = new int[m + 1];   
    for(int i = 0; i <= m; i++)
    order[i] = i-1;            // 注意这里order[0]=-1用来作为循环判断标识

    int count = 0;                               
    int k = m;
    bool flag = true;           // 标志找到一个有效组合
    while(order[0] == -1){
    if(flag){                   // 输出符合要求的组合
        for(i = 1; i <= m; i++) cout << a[order[i]] << " ";
        cout << endl;
        count++;
        flag = false;
    }

    order[k]++;                // 在当前位置选择新的数字
    if(order[k] == n){         // 当前位置已无数字可选，回溯
        order[k--] = 0;
        continue;
    }    

    if(k < m){                  // 更新当前位置的下一位置的数字         
        order[++k] = order[k-1];
        continue;
    }

    if(k == m)
        flag = true;
    }

    delete[] order;
    return count;
}

下面是测试以上函数的程序：
int main(){
    const int N = 4;
    const int M = 3;
    int a[N];
    for(int i=0; i<N; i++)
      a[i] = i+1;

    // 回溯方法
    cout << combine(a,N,3) << endl; 

    // 递归方法
    int b[M];
    combine(a,N,M,b,M); 

    return 0;
}

由上述分析可知，解决组合问题的通用算法不外乎递归和回溯两种。
在针对具体问题的时候，因为递归程序在递归层数上的限制，
对于大型组合问题而言，递归不是一个好的选择，
这种情况下只能采取回溯的方法来解决。