#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> kwayMerge(vector<vector<int>> &a) {
    if (a.empty()) return {};

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
    for(int i = 0; i < a.size(); i++) {
        q.push({a[i][0], i});
    }

    vector<int> res;
    vector<int> indexes(a.size(), 0);

    while(!q.empty()) {
        auto p = q.top();
        q.pop();
        res.push_back(p.first);
        int i = ++indexes[p.second];
        if (i == a[p.second].size()) continue;
        q.push({a[p.second][i], p.second});
    }

    return res;
}

// tuple
vector<int> kwayMerge1(vector<vector<int>>& a) {
    typedef tuple<int,int,int> tuple_t;
    auto comp = [](tuple_t& t1, tuple_t& t2) {return t1 > t2;};
    priority_queue<tuple_t, vector<tuple_t>, decltype(comp)> q(comp);
    for (int i = 0; i < a.size(); i++) {
        q.push(make_tuple(a[i][0], i, 0));
    }

    vector<int> res;
    while(!q.empty()) {
        auto tp = q.top();
        q.pop();
        res.push_back(get<0>(tp));
        int i = get<1>(tp), j = get<2>(tp) + 1;
        if (j == a[i].size()) continue;
        q.push(make_tuple(a[i][j], i, j));
    }
    return res;
}

void testKWayMerge() {
    vector<vector<int>> a = {
        {1, 3, 7},
        {5, 8},
        {2, 4, 6, 9}
    };

    auto res = kwayMerge1(a);
    for (auto v : res) cout << v << " "; cout << endl;
}

int main(int argc, char *argv[]) {
    testKWayMerge();
    return 0;
}
