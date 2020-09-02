#include <iostream>
#include <list>
#include <vector>

using namespace std;

// uni-directed
class Graph {
    int V;
    list<int> *adj;

public:
    Graph(int V) :V(V){
        adj = new list<int>[V];
    }

    void addEdge(int v, int w);
    void BFS(int s);
};

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}

void Graph::BFS(int s) {
    vector<bool> visited(V, false);

    list<int> q;
    visited[s] = true;
    list<int>::iterator it;
    q.push_back(s);

    while(!q.empty()) {
        s = q.front();
        cout << s << " ";
        q.pop_front();

        for (it = adj[s].begin(); it != adj[s].end(); it++) {
            if(!visited[*it]) {
                visited[*it] = true;
                q.push_back(*it);
            }
        }
    }
    cout << "\n";
}

void testBFS() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    g.BFS(2);

}

int main(int argc, char *argv[]) {
    testBFS();
    return 0;
}


