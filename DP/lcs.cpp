[LeetCode ] Longest Common Subsequence

// supporse:
// X = {A, B, C, B, D, A, B} 
// Y = {B, D, C, A, B, A}

// the longest common subsequence is of length 4 and they are {B,C,B,A} and {B,D,A,B}.


// Bottom up dynamic programming
// We can view the code above as just being a slightly smarter way of doing the original 
// recursive algorithm, saving work by not repeating subproblem computations. 
// But it can also be thought of as a way of computing the entries in the array L. 
// The recursive algorithm controls what order we fill them in, 
// but we'd get the same results if we filled them in in some other order. 
// We might as well use something simpler, like a nested loop, that visits the array systematically. 
// The only thing we have to worry about is that when we fill in a cell L[i,j], 
// we need to already know the values it depends on, namely in this case L[i+1,j], L[i,j+1], 
// and L[i+1,j+1]. For this reason we'll traverse the array backwards, from the last row 
// working up to the first and from the last column working up to the first. This is iterative
//  (because it uses nested loops instead of recursion) or bottom up (because the order 
// we fill in the array is from smaller simpler subproblems to bigger more complicated ones).


#include <iostream>
#include <vector>
using namespace std;

int max(int a,int b)
{
    return a>b?a:b;
}

int lcs(vector<char> A, vector<char> B){
    int m = A.size(), n = B.size();
    if(m == 0 || n == 0)
        return 0;

    // 创建动态二维数组  
    // int **lcs = new int*[m];  
    // for (int i = 0; i < m; ++i)
    //     lcs[i] = new int[n];  

    vector<vector<int>> L(m + 1, vector<int>(n + 1));

    int i, j;
    for (i = 0; i <= m; ++i){
        for (j = 0; j <= n; ++j)
        {
            if(i == 0 || j == 0)
                L[i][j] = 0;
            else if (A[i - 1] == B[j - 1])
                L[i][j] = 1 + L[i - 1][j - 1];
            else L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }

    // 以下代码是打印该LCS
    i = m, j = n;
    while(i && j)
    {
        if(A[i-1] == B[j-1] && L[i][j] == L[i-1][j-1] + 1)
        {
            // lcs[--k] = X[i-1];
            cout << A[i - 1];
            --i; --j;
        }else if(L[i-1][j] > L[i][j-1])
        {
            --i;
        }else
        {
            --j;
        }
    }

    cout << endl;

    return L[m][n];
}


// Reduced space complexity
// One disadvantage of the dynamic programming methods we've described, 
// compared to the original recursion, is that they use a lot of space: 
// O(mn) for the array L (the recursion only uses O(n+m)). 

// But the iterative version can be easily modified to use less space -- 
// the observation is that once we've computed row i of array L, we no longer need the values in row i+1.

// int lcs(char * A, char * B)
// {
//     // allocate storage for one-dimensional arrays X and Y
//     for (i = m; i >= 0; i--)
//     {
//         for (j = n; j >= 0; j--)
//         {
//         if (A[i] == '\0' || B[j] == '\0') X[j] = 0;
//         else if (A[i] == B[j]) X[j] = 1 + Y[j+1];
//         else X[j] = max(Y[j], X[j+1]);
//         }
//         Y = X;
//     }
//     return X[0];
// }

int main(){
    vector<char> X = {'A', 'B', 'C', 'B', 'D', 'A', 'B'};
    vector<char> Y = {'B', 'D', 'C', 'A', 'B', 'A'};

    // LCS: {B, C, B, A}, {B, D, A, B}
    cout <<"LCS:" << lcs(X, Y) << endl;
}

int lis(int A[], int n){
    vector<int> LS(n, 1);

    for(int i = 1; i < n; ++i){
        for(j = 0; j < i; ++j){
            if(A[j] < A[i] && LS[i] < LS[j] + 1)
                LS[i] = LS[j] + 1;
        }
    }

}