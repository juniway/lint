#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class UnionFind {
public:
    UnionFind(int n) {
        parents = vector<int>(n);
        ranks = vector<int>(n);

        for (int i = 0; i < n; i++)
            parents[i] = i;
    }

    int Find(int u) {
        while(parents[u] != u) {
            parents[u] = parents[parents[u]];
            u = parents[u];
        }
        return u;
    }

    bool Union(int u, int v) {
        int pu = Find(u), pv = Find(v);
        if (pu == pv) return false;
        if (ranks[pu] < ranks[pv])
            parents[pu] = pv;
        else if (ranks[pu] > ranks[pv])
            parents[pv] = pu;
        else {
            parents[pv] = pu;
            ranks[pu] += 1;
        }

        return true;
    }

private:
    vector<int> parents;
    vector<int> ranks;
};

int friendCircleNum(vector<vector<int>>& M) {
    int n = M.size();
    UnionFind uf(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++)
            if (M[i][j] == 1)
                uf.Union(i, j);
    }

    unordered_set<int> set;
    for (int i = 0; i < n; i++) {
        set.insert(uf.Find(i));
    }

    return set.size();
}

void testFriendCircleNum() {
    vector<vector<int>> friends = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };
    cout << friendCircleNum(friends) << endl;
}

int main(int argc, char *argv[]) {
    testFriendCircleNum();
    return 0;
}
