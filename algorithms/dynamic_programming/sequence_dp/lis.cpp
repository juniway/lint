// Longest Increasing Subsequence
// https://www.educative.io/edpresso/the-longest-increasing-subsequence-problem

#include <iostream>
#include <vector>

using namespace std;

int LIS(int arr[], int n, int i, int prev) {
    // Base case: if nothing is remaining
    if (i == n)
        return 0;

    // case 1: exclude the current element and process the remaining elements
    int exclude = LIS(arr, n, i + 1, prev);

    // case 2: include the current element if it is greater than previous element in LIS
    int include = 0;
    if (arr[i] > prev)
        include = 1 + LIS(arr, n, i + 1, arr[i]);

    // return maximum of above two choices
    return max(include, exclude);
}

int lis(vector<int>& A) {
    return LIS(&A[0], A.size(), 0, INT_MIN);
}

// tabulate: bottom up
int lisT(vector<int>& A) {
    if (A.size() == 0) return 0;
    vector<int> m(A.size(), 1);
    for (int i = 1; i < A.size(); i++) {
        for (int j = i - 1; j >= 0; j--) {
        // for(int j = 0; j < i; j++) {
            if (A[j] < A[i] && m[i] < 1 + m[j])
                m[i] = 1 + m[j];
        }
    }

    int ans = 1;
    for (auto x: m) {
        ans = max(ans, x);
    }
    return ans;
    // return *max_element(begin(m), end(m));
}


int lisA( int arr[], int n )  {
    vector<int> lis(n);
    lis[0] = 1;
    int maxLis = 0;
    for (int i = 1; i < n; i++ ) {
        lis[i] = 1;
        for (int j = 0; j < i; j++ )
            if ( arr[i] > arr[j] && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
                maxLis = max(maxLis, lis[i]);
            }

    }

    return lis[n-1];
}

int lisTail(vector<int>& A) {
    int n = A.size();
    const int INF = 1e9;
    vector<int> d(n + 1, INF);
    d[0] = -INF;
    for(int i = 0; i < n; i++) {
        for(int j = 1; j <= n; j++) {
            if(d[j - 1] < A[i] && d[j] > A[i])
                d[j] = A[i];
            else d[j] = A[i];
        }
    }

    int ans = 0;
    for (int i = 0; i <= n; i++) {
        if (d[i] < INF)
            ans = i;
    }

    return ans;
}

int lisBsearch(vector<int>const& a) {
    int n = a.size();
    const int inf = 1e9;
    vector<int> d(n+1, inf);
    d[0] = -inf;
    for (int i = 0; i < n; i++) {
        int j = upper_bound(d.begin(), d.end(), a[i]) - d.begin();
        if (d[j - 1] < a[i] && a[i] < d[j])
            d[j] = a[i];
    }

    int ans = 0;
    for (int i = 0; i <= n; i++) {
        if (d[i] < inf)
            ans = i;
    }

    return ans;
}

void testLis() {
    // vector<int> A{1, 7, 2, 8, 3, 4};
    // vector<int> A1{10,9,2,5,3,7,101,18};
    vector<int> A2{1,3,6,7,9,4,10,5,6};
    cout << lisT(A2) << endl;
    cout << lis(A2) << endl;
    cout << lisBsearch(A2) << endl;
    // cout << lisA(&A1[0], 8) << endl;
}

int main(int argc, char *argv[]) {
    testLis();
    return 0;
}
