#include <iostream>
#include <vector>
using namespace std;

int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

bool uni(int parent[], int u, int v) {
    int pu = find(parent, u);
    int pv = find(parent, v);
    if (pu == pv) return false;
    parent[u] = v;
    return true;
}

bool hasCycle(vector<vector<int>>& edges, int n) {
    vector<int> parent(n, -1);
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        if (!uni(&parent[0], u, v))
            return true;
    }
    return false;
}

void testUF() {
    vector<vector<int>> edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4}
    };
    cout << (hasCycle(edges, 5) ? "Yes" : "No") << endl;

    vector<vector<int>> edges1 = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 1}
    };
    cout << (hasCycle(edges1, 5) ? "Yes" : "No") << endl;
}

int main(int argc, char *argv[]) {
    testUF();
    return 0;
}
