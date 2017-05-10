#include <iostream>
#include <vector>

using namespace std;

// 01 背包
// N 件物品，第 i 件物品的大小是 w[i]，其价值是 v[i]
// V 表示背包大小

// 用 dp[i][j] 表示前 i 件物品放入一个容量为 j 的背包可以获得的最大价值。注意，这里的前 i 个，而 dp[i] 一共有 i + 1 个元素。

// 注意, 这里的 dp[i][j] 可以有两种理解:
// 1. dp[i][j] 可以表示前 i 个物品，不包括当前的 w[i] 元素，相当于 w[0 ... i-1]，注意 [0, i - 1] 这个区间一共是 i 个元素。
// 2. dp[i][j] 也可以表示前 i 个物品，包括当前的 w[i] 元素，这样的话，dp[0] 相当于就是第 0 个元素了，在遇到有 dp[i-1] 时可能遇到麻烦。

// 状态转移方程:
// 1) 前 i - 1 个物品，放入容量为 j 的包内，前 i - 1 个物品，放入容量为 j - w[i - 1] 的包内,
//    价值为 c[i - 1][j - w[i - 1]] + v[i - 1]
// 2) 前 i - 1 个物品，放入容量为 j 的包内，前 i - 1 个物品，放入容量为 j - w[i] 的包内，
//    价值为 c[i - 1][j - w[i]]


// int c[10][100] = {0}; // N,V 相当于 n, m

void print_vec1(const vector<vector<int>> & vec);
void knap(int m, vector<int> w, vector<int> v){ // m 是背包容量
    int n = v.size();   // 物品个数

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    for(int j = 0; j <= m; ++j) { // 初始值：不管背包多大，放 0 个物品，总价值都为 0
        dp[0][j] = 0;
    }

    // for(int i = 1; i <= n; ++i) {
    //     for(int j = 0; j <= m; ++j) {
    //         if(j < w[i - 1])
    //             dp[i][j] = dp[i - 1][j];
    //         else
    //             dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i - 1]] + v[i - 1]);
    //     }
    // }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(j < w[i])
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
        }
    }

    print_vec1(dp);

    cout << "knap max: " << dp[n][m] << endl;
}




// 滚动数组：
int B[20]; // 背包容量
void knap1(int m, vector<int> w, vector<int> v){
    int n = w.size();

    for(int j = 0; j <= m; ++j){
        B[j] = 0;
    }

    for(int i = 1; i < n; ++i){
        for(int j = m; j >= w[i]; --j){
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
int knap_recursive(int m, vector<int> w, vector<int> v, int n){
    // Base case
    if(n == 0 || m == 0)
        return 0;
    // If weight of the nth item is more than Knapsack capacity m,
    // then this item cannot be included in the optimal solution
    if(w[n-1] > m)
        return knap_recursive(m, w, v, n - 1);
    else
        // Return the maximum of two cases:
        // (1) nth item included
        // (2) nth item not included
        return max(v[n - 1] + knap_recursive(m - w[n - 1], w, v, n - 1), knap_recursive(m, w, v, n-1));
}

// void print_vec(int m, int n){
//     for(int i = 0; i <= m; ++i){
//         for(int j = 0; j <= n; ++j){
//             printf("%d ", c[i][j]);
//         }
//         printf("\n");
//     }
//     printf("\n");
// }

void print_vec1(const vector<vector<int>> &vec) {
    for (auto &vi : vec) {
        for (auto &vj : vi) {
            cout << vj << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int main(){
    int capacity = 15; // 背包容量
    vector<int> inputw = {3, 4, 5, 6};  // 物品个数是数组大小，也即 4
    vector<int> inputv = {4, 5, 6, 7};  // 同上
    knap(capacity, inputw, inputv);

    // knap1(capacity, inputw, inputv);
//     knap1(capacity, inputw, inputv);
//     int res = knap_recursive(capacity, inputw, inputv, 5);
//     printf("B[15] = %d \n", B[15]);
//     print_vec(4, 15);
//     printf("max: %d\n", res);
//     printf("max1: %d\n", c[4][15]);
}

