#include <algorithm>
#include <iostream>
#include <vector>
#include "../binarytree/tree.hpp"

using namespace std;

vector<int> findVertexCover(vector<int> edges[], int N) {
    vector<int> res;
    vector<int> visited(N, false);
    for (int u = 0; u < N; u++) {
        if (!visited[u]) {
            for (int v = 0; v < edges[u].size(); v++) {
                if (!visited[edges[u][v]]) {
                    res.push_back(u);
                    res.push_back(edges[u][v]);
                    visited[u] = true;
                    visited[edges[u][v]] = true;
                    break;
                }
            }
        }
    }
    return res;
}


void testVertexCover() {
    const int N = 7;
    vector<int> edges[N];
    edges[0].push_back(1);
    edges[0].push_back(2);
    edges[1].push_back(3);
    edges[3].push_back(4);
    edges[4].push_back(5);
    edges[5].push_back(6);
    auto res = findVertexCover(edges, N);
    for (auto n : res) cout << n << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    testVertexCover();
    return 0;
}

