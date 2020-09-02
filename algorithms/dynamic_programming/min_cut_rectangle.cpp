#include <iostream>
using namespace std;

int min_cut(int m, int n) {
    if (m == n) return 0;
    int cut_horizontal = INT_MAX;
    for (int i = 1; i <= m/2; i++) {
         cut_horizontal = min (cut_horizontal, min_cut(m - i, n) + min_cut(i, n));
    }

	int cut_vertical = INT_MAX;
    for (int i = 1; i <= n/2; i++) {
    	cut_vertical = min (cut_vertical, min_cut(m, i) + min_cut(m, n - i));
    }
    return min(cut_horizontal, cut_vertical) + 1;
}


const int MAXN = 300;
int dp[MAXN][MAXN];

// memo
int minCut(int m, int n) {
    if (m == n) return 1;
    if (dp[m][n]) return dp[m][n];

    int hori = INT_MAX, vert = INT_MAX;
    for (int i = 1; i <= m/2; i++)
        hori = min(hori, minCut(i, n) + minCut(m - i, n));

    for (int i = 1; i <= n/2; i++)
        vert = min(vert, minCut(m, i) + minCut(m, n - i));

    int mixed = INT_MAX;
    for (int i = 1; i < m - 1; i++) {
        for (int i1 = m - 1; i1 > i; i1--) {
            for(int j = 1; j < n - 1; j++) {
                for (int j1 = n - 1; j1 > j; j1--) {
                    int m1 = minCut(i, j1);
                    int m2 = minCut(m - i, j);
                    int m3 = minCut(i1, n - j1);
                    int m4 = minCut(m - i1, n -j);
                    int m0 = minCut(i1 - i, j1 - j);
                    if (i == 4 && i1 == 5 && j == 7 && j1 == 8) {
                        // cout << "m1: " << "(" << i << ", " << j1 << ")" << endl;
                        // cout << "m2: " << "(" << m - i << ", " << j << ")" << endl;
                        // cout << "m3: " << "(" << i1 << ", " << n - j1 << ")" << endl;
                        // cout << "m4: " << "(" << m - i1 << ", " << n - j << ")" << endl;
                        // cout << "m5: " << "(" << i1 - i << ", " << j1 - j << ")" << endl;
                        // cout << m1 << ", " << m2 << " " << m3 << " " << m4 << " " << m0 << endl;
                        // int mall = m0 + m1 + m2 + m3 + m4;
                        // cout << "mixed: " << mixed << ", mall: " << mall << endl;
                    }

                    mixed = min(mixed, m1 + m2 + m3 + m4 + m0);
                }
            }
        }
    }


    return dp[m][n] = min(mixed, min(hori, vert));
}

void testMinCut() {
    // cout << min_cut(4, 3) << ", " << minCut(4, 3) << endl;
    // cout << min_cut(5, 4) << ", " << minCut(5, 4) << endl;
    // cout << min_cut(2, 1) << ", " << minCut(2, 1) << endl;
    // cout << min_cut(3, 2) << ", " << minCut(3, 2) << endl;
    // cout << min_cut(6, 5) << ", " << minCut(6, 5) << endl;
    // cout << min_cut(1, 1) << ", " << minCut(1, 1) << endl;
    // cout << min_cut(11, 13) << ", " << minCut(11, 13) << endl;
    // cout << min_cut(30, 35) << endl;
    // cout << minCut(30, 35) << endl;

    // cout << minCut(2, 3) << endl;
    // cout << minCut(5, 8) << endl;
    cout << minCut(11, 13) << endl;
    cout << minCut(36, 30) << endl;
}

int main(int argc, char *argv[]) {
    testMinCut();
    return 0;
}
