һ���ַ���S��ȥ��������߶��Ԫ����ʣ�µ��Ӵ���ΪS�������С�����������о���Ѱ�������������е������У�������������������������ͬ��˳����֣����ǲ���Ҫ�������ġ�

��������X=ABCBDAB��Y=BDCABA������BCA��X��Y��һ�����������У����ǲ���X��Y������������У�������BCBA��X��Y��һ��LCS������BDABҲ�ǡ�

Ѱ��LCS��һ�ַ�����ö��X���е������У�Ȼ��ע�����Ƿ���Y�������У�����ʱ��¼���ֵ�������С�����X��m��Ԫ�أ���X��2^m�������У�ָ������ʱ�䣬�Գ����в�ʵ�ʡ�

ʹ�ö�̬�滮���������⣬��Ѱ�������ӽṹ����X=<x1,x2,��,xm>��Y=<y1,y2,��,yn>Ϊ�������У�LCS(X,Y)��ʾX��Y��һ������������У����Կ���

���xm=yn����LCS ( X,Y ) = xm + LCS ( Xm-1,Yn-1 )��
���xm!=yn����LCS( X,Y )= max{ LCS ( Xm-1, Y ), LCS ( X, Yn-1 ) }
LCS����Ҳ�����ص����������ʣ�Ϊ�ҳ�X��Y��һ��LCS��������Ҫ��X��Yn-1��һ��LCS�Լ�Xm-1��Y��һ��LCS���������������ⶼ��������Xm-1��Yn-1��һ��LCS���ȵ�.


DP���մ���Ļ�����ֵ����ֵ�����Ž⣩���ҵ�������ֵ�����ҵ������ŷ�����Ϊ���ҵ����LCS�����Ƕ���dp[i][j]��¼����LCS�ĳ��ȣ��Ϸ�״̬�ĳ�ʼֵΪ������X�ĳ���Ϊ0��Y�ĳ���Ϊ0������������LCS����Ϊ0����dp[i][j]=0��������i��j�ֱ��ʾ����X�ĳ��Ⱥ�����Y�ĳ��ȣ�״̬ת�Ʒ���Ϊ

dp[i][j] = 0  ���i=0��j=0
dp[i][j] = dp[i-1][j-1] + 1  ���X[i-1] = Y[i-1]
dp[i][j] = max{ dp[i-1][j], dp[i][j-1] }  ���X[i-1] != Y[i-1]
���������������еĳ��Ⱥ����LCS�������dp�����ŷ����ˣ�����01�������Ѿ��������ȿ�����һ������ľ���洢·����Ҳ����ֱ�Ӹ���״̬ת�ƾ��������ŷ�����

�������£�

#include <iostream>
using namespace std;
 
/* LCS
 * �����г��ȶ�������20
*/
 
int dp[21][21]; /* �洢LCS����, �±�i,j��ʾ����X,Y���� */
char X[21];
char Y[21];
int i, j;
 
void main()
{
    cin.getline(X,20);
    cin.getline(Y,20);
 
    int xlen = strlen(X);
    int ylen = strlen(Y);
 
    /* dp[0-xlen][0] & dp[0][0-ylen] ���ѳ�ʼ��0 */
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
 
    /* ���LCS �����������ӡ�ģ�����дһ�ݹ麯����������ӡ
       ������õķ����ǽ�Y��Ϊ��ʱ�洢LCS�����飬������Y
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
