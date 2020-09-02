#include <iostream>
#include <vector>
using namespace std;
const int MAXLEN = 100;

int dp[MAXLEN];
bool v[MAXLEN];

// since v can be any value(including negative), we can't use integer to signal return
// so we use an extra array to signal

int maxSum(vector<int>& A, int n, int i) {
    if (i >= n) return 0;
    if (v[i]) return dp[i];
    dp[i] = max(maxSum(A, n, i+1), A[i] + maxSum(A, n, i + 2));
    v[i] = true;

    return dp[i];
}

int maxSum1(vector<int>& A, int n, int i) {
    if (n == 0) return 0;
    if (v[i]) return dp[i];
    v[i] = true;
    dp[i] = max(maxSum(A, n, i - 1), A[i] + maxSum(A, n, i - 2));

    return dp[i];
}

int noAdjacentSum(vector<int>& A) {
    cout << maxSum(A, A.size(), 0) << endl;
    cout << maxSum(A, A.size(), 0) << endl;
    return 0;
}

int noAdjacentSum1(vector<int>& A) {
    int n = A.size();
    vector<int> m(n + 1, INT_MIN);
    m[0] = 0, m[1] = A[0];
    for (int i = 1; i < n; i++) {
        m[i+1] = max(m[i], m[i-1] + A[i]);
        m[i+1] = max(m[i+1], A[i]);
    }

    return m[n];
}

void testMaxSum() {
    vector<int> A{-2, 1, 3, -4, 5};
    cout << noAdjacentSum(A) << endl;
    // cout << noAdjacentSum1(A) << endl;
}

int main(int argc, char *argv[]) {
    testMaxSum();
    return 0;
}
