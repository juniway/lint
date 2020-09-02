#include <vector>
#include <list>

struct Graph {
    static constexpr int V = 8;
    std::vector<int> edges[V];
    void BuildSimpleGraph() {
        edges[0].push_back(1);
        edges[0].push_back(2);
        edges[1].push_back(3);
        edges[3].push_back(4);
        edges[4].push_back(5);
        edges[5].push_back(6);
        edges[1].push_back(5);
    }
};

struct Graph1 {
    static constexpr int V = 7;
    std::list<int> edges[V];
    void BuildSimpleGraph() {
        edges[0].push_back(1);
        edges[0].push_back(2);
        edges[1].push_back(3);
        edges[3].push_back(4);
        edges[4].push_back(5);
        edges[5].push_back(6);
    }
};

struct Graph2 {
    static constexpr int V = 5;
    std::vector<int> edges[V];
    void BuildSimpleGraph() {
        edges[0].push_back(1);
        edges[1].push_back(2);
        edges[2].push_back(3);
        edges[3].push_back(4);
    }
};
