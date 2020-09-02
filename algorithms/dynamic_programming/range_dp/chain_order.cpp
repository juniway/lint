#include <iostream>
#include <vector>
using namespace std;

// i and j represents the begin and end of part
int chainOrder(vector<int>& p, int i, int j) {
    if (i == j) return 0;
    int chain, minChain = INT_MAX;
    for (int k = i; k < j; k++) {
        chain = chainOrder(p, i, k) + chainOrder(p, k + 1, j) + p[i - 1]*p[k]*p[j];
        minChain = min(minChain, chain);
    }

    return minChain;
}

// time: O(N^3)
// space: O(N^2)
int chainOrder(vector<int>& p, int n) {
    vector<vector<int>> m(n, vector<int>(n, INT_MAX));
    int i, j, k, L, chain;
    for (int i = 1; i < n; i++)
        m[i][i] = 0;

    for (L = 2; L < n; L++) {
        for (i = 1; i < n - (L - 1); i++) {
            j = i + L - 1;
            for (k = i; k < j; k++) {
                chain = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (m[i][j] > chain)
                    m[i][j] = chain;
            }
        }
    }
    return m[1][n - 1];
}

void testChainOrder() {
    vector<int> p {40, 20, 30, 10, 30};
    // vector<int> p {2, 40, 2, 40, 5};
    cout << chainOrder(p, 1, p.size() - 1) << endl; // 26000
}

int main(int argc, char *argv[]) {
    testChainOrder();
    return 0;
}

