#include <iostream>
#include <vector>

using std::cout;
using std::vector;
using std::max;

int rob(vector<int>& A, int k, vector<int> & memo) {
    if (k < 0) return 0;
    if (memo[k] >= 0) {
        return memo[k];
    }

    memo[k] =  max(rob(A, k - 2, memo) + A[k], rob(A, k - 1, memo));
    return memo[k];
}

int rob(vector<int>& a) {
    vector<int> memo(a.size() + 1, -1);
    int res =  rob(a, a.size() - 1, memo);
    return res;
}

// bottom up
int rob1(vector<int>& A) {
    vector<int> tab(A.size() + 1, -1);
    tab[0] = 0;
    tab[1] = A[0];
    for(int i = 1; i < A.size(); i++) {
        tab[i+1] = max(tab[i-1] + A[i], tab[i]);
    }
    return tab[A.size()];
}

// two variables
int rob2(vector<int>& A) {
    if (A.size() == 0) return 0;
    int prev1 = 0, prev2 = 0;
    for (int a : A) {
        int tmp = prev1;
        prev1 = max(prev2 + a, prev1);
        prev2 = tmp;
    }

    return prev1;
}

int main(int argc, char *argv[]) {
    vector<int> A{2, 7, 9, 3, 1};
    std::cout << rob(A) << "\n";
    return 0;
}
