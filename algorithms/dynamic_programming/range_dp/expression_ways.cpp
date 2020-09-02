#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> waysToCompute(string input) {
    vector<int> nums;
    vector<char> ops;
    for (char c : input) {
        if(isdigit(c)) nums.push_back(c - '0');
        else ops.push_back(c);
    }

    int n = nums.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>()));
    for (int i = 0; i < n; i++) dp[i][i].push_back(nums[i]);

    // for (int i = 0; i < n; i++) {
    //     for (int j = i; j >= 0; j--) {
    //         for (int k = j; k < i; k++) {
    //             for (int left : dp[j][k])
    //                 for(int right : dp[k + 1][i]) {
    //                     int val = 0;
    //                     switch(ops[k]) {
    //                         case '+': val = left + right; break;
    //                         case '-': val = left - right; break;
    //                         case '*': val = left * right; break;
    //                     }
    //                     dp[j][i].push_back(val);
    //                 }
    //         }
    //     }
    // }

    for (int l = 2; l <= n; l++) {
        for (int i = 0; i < n -l + 1; i++) {
            int j = i + l - 1;
            for (int k = i; k < j; k++) {
                for (int left : dp[i][k]) {
                    for (int right : dp[k + 1][j]) {
                        int val = 0;
                        switch(ops[k]) {
                            case '+': val = left + right; break;
                            case '-': val = left - right; break;
                            case '*': val = left * right; break;
                        }
                        dp[i][j].push_back(val);
                    }
                }
            }
        }
    }
    return dp[0][n - 1];
}

void testWaysToCompute() {
    auto res = waysToCompute("1-1+2");
    for (auto v : res) cout << v << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    testWaysToCompute();
    return 0;
}
