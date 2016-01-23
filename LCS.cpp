一个字符串S，去掉零个或者多个元素所剩下的子串称为S的子序列。最长公共子序列就是寻找两个给定序列的子序列，该子序列在两个序列中以相同的顺序出现，但是不必要是连续的。

例如序列X=ABCBDAB，Y=BDCABA。序列BCA是X和Y的一个公共子序列，但是不是X和Y的最长公共子序列，子序列BCBA是X和Y的一个LCS，序列BDAB也是。

寻找LCS的一种方法是枚举X所有的子序列，然后注意检查是否是Y的子序列，并随时记录发现的最长子序列。假设X有m个元素，则X有2^m个子序列，指数级的时间，对长序列不实际。

使用动态规划求解这个问题，先寻找最优子结构。设X=<x1,x2,…,xm>和Y=<y1,y2,…,yn>为两个序列，LCS(X,Y)表示X和Y的一个最长公共子序列，可以看出

如果xm=yn，则LCS ( X,Y ) = xm + LCS ( Xm-1,Yn-1 )。
如果xm!=yn，则LCS( X,Y )= max{ LCS ( Xm-1, Y ), LCS ( X, Yn-1 ) }
LCS问题也具有重叠子问题性质：为找出X和Y的一个LCS，可能需要找X和Yn-1的一个LCS以及Xm-1和Y的一个LCS。但这两个子问题都包含着找Xm-1和Yn-1的一个LCS，等等.


DP最终处理的还是数值（极值做最优解），找到了最优值，就找到了最优方案；为了找到最长的LCS，我们定义dp[i][j]记录序列LCS的长度，合法状态的初始值为当序列X的长度为0或Y的长度为0，公共子序列LCS长度为0，即dp[i][j]=0，所以用i和j分别表示序列X的长度和序列Y的长度，状态转移方程为

dp[i][j] = 0  如果i=0或j=0
dp[i][j] = dp[i-1][j-1] + 1  如果X[i-1] = Y[i-1]
dp[i][j] = max{ dp[i-1][j], dp[i][j-1] }  如果X[i-1] != Y[i-1]
求出了最长公共子序列的长度后，输出LCS就是输出dp的最优方案了，这在01背包中已经讲过，既可以用一个额外的矩阵存储路径，也可以直接根据状态转移矩阵倒推最优方案。

代码如下：

#include <iostream>
using namespace std;
 
/* LCS
 * 设序列长度都不超过20
*/
 
int dp[21][21]; /* 存储LCS长度, 下标i,j表示序列X,Y长度 */
char X[21];
char Y[21];
int i, j;
 
void main()
{
    cin.getline(X,20);
    cin.getline(Y,20);
 
    int xlen = strlen(X);
    int ylen = strlen(Y);
 
    /* dp[0-xlen][0] & dp[0][0-ylen] 都已初始化0 */
    for(i = 1; i <= xlen; ++i)
    {
        for(j = 1; j <= ylen; ++j)
        {
            if(X[i-1] == Y[j-1])
            {
                dp[i][j] = dp[i-1][j-1] + 1;
            }else if(dp[i][j-1] > dp[i-1][j])
            {
                dp[i][j] = dp[i][j-1];
            }else
            {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    printf("len of LCS is: %d\n", dp[xlen][ylen]);
 
    /* 输出LCS 本来是逆序打印的，可以写一递归函数完成正序打印
       这里采用的方法是将Y作为临时存储LCS的数组，最后输出Y
    */
    i = xlen;
	j = ylen;
	int k = dp[i][j];
	char lcs[21] = {'\0'};
	while(i && j)
	{
		if(X[i-1] == Y[j-1] && dp[i][j] == dp[i-1][j-1] + 1)
		{
			lcs[--k] = X[i-1];
			--i; --j;
		}else if(X[i-1] != Y[j-1] && dp[i-1][j] > dp[i][j-1])
		{
			--i;
		}else
		{
			--j;
		}
	}
	printf("%s\n",lcs);
}


#include<iostream>
#include<string.h>
using namespace std;
 
// A utility function to find maximum of two integers
int max(int a, int b)
{   return (a > b)? a : b; }
 
// Returns length of longest common substring of X[0..m-1] and Y[0..n-1]
int LCSubStr(char *X, char *Y, int m, int n){
    // Create a table to store lengths of longest common suffixes of
    // substrings.   Notethat LCSuff[i][j] contains length of longest
    // common suffix of X[0..i-1] and Y[0..j-1]. The first row and
    // first column entries have no logical meaning, they are used only
    // for simplicity of program
    int **LCSuff = new int*[m+1];
    for(int i=0; i<m+1; i++)
    	LCSuff[i] = new int[n+1];
    	
    int result = 0;  // To store length of the longest common substring
 
    /* Following steps build LCSuff[m+1][n+1] in bottom up fashion. */
    for (int i=0; i<=m; i++){
        for (int j=0; j<=n; j++){
            if (i == 0 || j == 0)
                LCSuff[i][j] = 0;
 
            else if (X[i-1] == Y[j-1]){
                LCSuff[i][j] = LCSuff[i-1][j-1] + 1;
                result = max(result, LCSuff[i][j]);
            }
            else LCSuff[i][j] = 0;
        }
    }
    for(int i=0; i<m+1; i++)
    	delete [] LCSuff[i];
    delete [] LCSuff;
    return result;
}
 
/* Driver program to test above function */
int main(){
    char X[] = "OldSite:GeeksforGeeks.org";
    char Y[] = "NewSite:GeeksQuiz.com";
 
    int m = strlen(X);
    int n = strlen(Y);
 
    cout << "Length of Longest Common Substring is " << LCSubStr(X, Y, m, n);
    cout <<endl;
    return 0;
}
