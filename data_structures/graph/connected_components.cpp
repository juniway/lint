#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int find(vector<int>& parents, int id) {
    while(parents[id] != id) {
        parents[id] = parents[parents[id]];
        id = parents[id];
    }
    return id;
}

int countComponents(int n, vector<vector<int>>& edges) {
    vector<int> parents(n);
    for (int i = 0; i < n; i++)
        parents[i] = i;

    for(auto edge : edges) {
        int pu = find(parents, edge[0]);
        int pv = find(parents, edge[1]);
        if (pu != pv) {
            parents[pu] = pv;
            n--;
        }
    }

    return n;
}

void testConnectedComponents() {
    vector<vector<int>> edges = {
        {0, 1}, {1, 2}, {3, 4}
    };

    cout << countComponents(5, edges) << endl;
}

int main(int argc, char *argv[]) {
    testConnectedComponents();
    return 0;
}
