#include <iostream>
#include <vector>


// 状态转移方程:
// 1) 前 i - 1 个物品，放入容量为 j 的包内，前 i - 1 个物品，放入容量为 j - w[i - 1] 的包内,
//    价值为 c[i - 1][j - w[i - 1]] + v[i - 1]
// 2) 前 i - 1 个物品，放入容量为 j 的包内，前 i - 1 个物品，放入容量为 j - w[i] 的包内，
//    价值为 c[i - 1][j - w[i]]
using namespace std;

int c[10][100] = {0};

void knap(int m, vector<int> w, vector<int> v){
    int n = v.size();

    for(int j = 0; j <= m; ++j){
        c[0][j] = 0;
    }

    for(int i = 1; i <= n; ++i){
        for(int j = 0; j <= m; ++j){
            if(j < w[i - 1]) c[i][j] = c[i - 1][j];
            else
                c[i][j] = max(c[i-1][j], c[i-1][j-w[i-1]] + v[i-1]);
        }
    }
}


// 滚动数组：
int B[20];
void knap1(int W, vector<int> w, vector<int> v){
    int n = w.size();

    for(int j = 0; j <= W; ++j){
        B[j] = 0;
    }

    for(int i = 1; i < n; ++i){
        for(int j = W; j >= w[i]; --j){
            // if(B[j] < B[j - w[i]] + v[i]) 
              //  B[j] = B[j - w[i]] + v[i];
            
            B[j] = max(B[j], B[j - w[i]] + v[i]);

            printf("%d ", B[j]);
        }
        printf("\n");
    }
    // for(int i = 1; i <= 15; ++i){
    //     printf("%d ", B[i]);
    // }
    printf("\n");
}

// a naive recursive implementation of 0-1 knapsack problem
int knap_recursive(int W, vector<int> w, vector<int> v, int n){
    // Base case
    if(n == 0 || W == 0)
        return 0;
    // If weight of the nth item is more than Knapsack capacity W,
    // then this item cannot be included in the optimal solution
    if(w[n-1] > W)
        return knap_recursive(W, w, v, n - 1);
    else
        // Return the maximum of two cases:
        // (1) nth item included
        // (2) nth item not included
        return max(v[n - 1] + knap_recursive(W - w[n - 1],w, v, n - 1), knap_recursive(W, w, v, n-1));
}

void printvec(int m, int n){
    for(int i = 0; i <= m; ++i){
        for(int j = 0; j <= n; ++j){
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    int capacity = 15;
    vector<int> inputw = { 3, 4, 5, 6};
    vector<int> inputv = { 4, 5, 6, 7};
    knap(capacity, inputw, inputv);
    // knap1(capacity, inputw, inputv);
    knap1(capacity, inputw, inputv);
    int res = knap_recursive(capacity, inputw, inputv, 5);
    printf("B[15] = %d \n", B[15]);
    printvec(4, 15);
    printf("max: %d\n", res);
    printf("max1: %d\n", c[4][15]);
}

