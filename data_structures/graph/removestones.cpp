#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<int, int> f;
int islands = 0;

int find(int id) {
    if (f.count(id) == 0) f[id] = id, islands++;
    if (id != f[id]) f[id] = f[f[id]];
    return f[id];
}

void uni(int u, int v) {
    int i = u, j = v;
    u = find(u), v = find(v);
    printf("before: %d => %d\n", i, u);
    printf("before: %d => %d\n", j, v);
    if (u != v) {
        f[u] = v;
        islands--;
    }
    printf("after: %d => %d\n\n", u, v);
}

int removeStones(vector<vector<int>>& stones) {
    for (int i = 0; i < stones.size(); i++) {
        uni(stones[i][0], ~stones[i][1]);
    }
    return stones.size() - islands;
}

void testRemoveStones() {
    vector<vector<int>> stones = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 2},
        {2, 1},
        {2, 2},
    };
    cout << removeStones(stones) << endl;
}

int main(int argc, char *argv[]) {
    testRemoveStones();
    return 0;
}
