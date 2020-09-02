#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    unordered_map<long long, int> set;
    int res = INT_MAX;
    int tilingRectangle(int n, int m) {
        if (n == m) return 1;
        if (n > m) {
            int temp = n;
            n = m;
            m = temp;
        }

        dfs(n, m, vector<int>(n + 1), 0);
        return res;
    }

    void dfs(int n, int m, vector<int> h, int cnt) {
        if (cnt >= res) return;
        bool isFull = true;
        int pos = -1, minH = INT_MAX;
        for (int i = 1; i <= n; i++) {
            if (h[i] < m) isFull = false;
            if (h[i] < minH) {
                pos = i;
                minH = h[i];
            }
        }
        if (isFull) {
            res = min(cnt, res);
            return;
        }

        long key = 0, base = m + 1;
        for (int i = 1; i <= n; i++) {
            key += h[i] * base;
            base *= m + 1;
        }
        if (set.find(key) != set.end() && set[key] <= cnt) return;
        set[key] = cnt;

        int end = pos;
        while (end + 1 <= n && h[end + 1] == h[pos] && (end + 1 - pos + 1 + minH) <= m) end++;
        for (int j = end; j >= pos; j--) {
            int curH = j - pos + 1;

            // int[] next  = Arrays.copyOf(h, n + 1);
            vector<int> next(h.begin(), h.begin() + n + 1);
            for (int k = pos; k <= j; k++) {
                next[k] += curH;
            }
            dfs(n, m, next, cnt + 1);
        }

    }
};

void testTilingSquares() {
    Solution sol;
    cout << sol.tilingRectangle(54, 43) << endl;
}

int main(int argc, char *argv[]) {
    testTilingSquares();
    return 0;
}
