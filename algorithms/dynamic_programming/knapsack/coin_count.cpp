#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int count(vector<int>& S, int k, int n) {
    if (n == 0) return 1;
    if (n < 0) return 0;
    if (k == S.size()) return 0;

    return count(S, k, n - S[k]) + count(S, k + 1, n);
}

//
int count(vector<int>& S, int N) {
    if (N < 0) return 0;
    int n = S.size();
    vector<vector<int>> cnt(N + 1, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        cnt[0][i] = 1;
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < n; j++) {
            int x = j - 1 >= 0 ? cnt[i][j-1]:0;
            int y = i >= S[j] ? cnt[i-S[j]][j]:0;
            cnt[i][j] = x + y;
        }
    }
    for (auto x: cnt) {
        for (auto a:x) cout << a << " ";
        cout << endl;
    }
    return cnt[N][n-1];
}

int count0(vector<int>& S, int N) {
    if (N < 0) return 0;
    int n = S.size();
    vector<vector<int>> cnt(n, vector<int>(N + 1, 0));
    for (int i = 0; i < n; ++i) {
        cnt[i][0] = 1;
    }
    for (int j = 0; j < n; j++) {
        for (int i = 1; i <= N; i++) {
            int x = j >= 1 ? cnt[j-1][i]:0;
            int y = i - S[j] >= 0 ? cnt[j][i-S[j]]:0;
            cnt[j][i] = x + y;
        }
    }
    for (auto x: cnt) {
        for (auto a:x) cout << a << " ";
        cout << endl;
    }
    return cnt[n - 1][N];
}
int count1(vector<int>& S, int N) {
    int n = S.size();
    int i, j, x, y;
    vector<vector<int>> cnt(N + 1, vector<int>(n, 0));
    for (i = 0; i < n; ++i) {
        cnt[0][i] = 1;
    }

    for (i = 1; i < N + 1; ++i) {
        for (j = 0; j < n; ++j) {
            x = (i-S[j] >= 0) ? cnt[i - S[j]][j]:0;
            y = (j >= 1) ? cnt[i][j-1]:0;
            cnt[i][j] = x + y;
        }
    }

    for (auto x: cnt) {
        for (auto a:x) cout << a << " ";
        cout << endl;
    }
    return cnt[N][n-1];
}

// space optimize
int countO(vector<int>& S, int N) {
    vector<int> cnt(N + 1, 0);
    cnt[0] = 1;
    for (int i = 0; i < S.size(); i++)
        for(int j = S[i]; j < N + 1; j++) {
            cnt[j] += cnt[j-S[i]];
    }

    return cnt[N];
}

void testCount() {
    vector<int> S {1, 2, 3};
    vector<pair<vector<int>, int>> Ss {
        {{1, 2, 3}, 4}, // 4
        {{1, 2, 5}, 5}, // 4
        {{2, 5, 3, 6}, 10}, // 5
    };

    for (int i = 0; i < S.size(); i++) {
        cout << count(Ss[i].first, 0, Ss[i].second) << endl;
    }
}

void testCnt() {
    vector<int> S {1, 2, 3};
    vector<pair<vector<int>, int>> Ss {
        {{1, 2, 3}, 4}, // 4
        {{1, 2, 5}, 5}, // 4
        {{2, 5, 3, 6}, 10}, // 5
    };

    for (int i = 0; i < S.size(); i++) {
        // cout << count(Ss[i].first, Ss[i].second) << endl;
        cout << count0(Ss[i].first, Ss[i].second) << endl;
        // cout << count1(Ss[i].first, Ss[i].second) << endl;
    }
}

int main(int argc, char *argv[]) {
    // testCount();
    testCnt();
    return 0;
}
