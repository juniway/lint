#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> mergeTwo(vector<int>& a, vector<int>& b) {
    if (a.empty()) return b;
    if (b.empty()) return a;
    vector<int> res(a.size() + b.size());
    int i = 0, j = 0, k = 0;
    for (; k < a.size() + b.size(); k++) {
        if (i == a.size()) res[k] = b[j++];
        else if (j == b.size()) res[k] = a[i++];
        else if (a[i] > b[j]) res[k] = b[j++];
        else res[k] = a[i++];
    }

    return res;
}

// bottom up
vector<int> kWayMerge(vector<vector<int>>& a) {
    if (a.empty()) return {};
    while (a.size() > 1) {
        vector<vector<int>> tmp;
        for (int i = 0; i < a.size() - 1; i += 2) {
            auto m = merge(a[i], a[i + 1]);
            tmp.push_back(m);
        }
        if (a.size() % 2 == 1) tmp.push_back(a[a.size() - 1]);
        a = tmp;
    }
    return a[0];
}

// top down
vector<int> kWayMerge(vector<vector<int>>& a, int left, int right) {
    if (left == right) return a[left];
    int mid = left + (right - left) / 2;
    auto low = kWayMerge(a, left, mid);
    auto high = kWayMerge(a, mid + 1, right);
    return merge(low, high);
}

// top down
vector<int> kWayMerge1(vector<vector<int>>& a) {
    return kWayMerge(a, 0, a.size() - 1);
}

// heap + pair
vector<int> kWayMerge2(vector<vector<int>>& a) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int i = 0; i < a.size(); i++) {
        pq.push(make_pair(a[i][0], i));
    }

    vector<int> res;
    vector<int> indexs(a.size(), 0);
    while (!pq.empty()){
        auto v = pq.top();
        res.push_back(v.first);
        pq.pop();
        int i = ++indexs[v.second];
        if (i == a[v.second].size()) continue;
        pq.push(make_pair(a[v.second][i], v.second));
    }

    return res;
}

// heap + tuple
vector<int> kWayMerge3(vector<vector<int>>& a) {
    auto compare = [](tuple<int, int, int>& t1, tuple<int, int, int>& t2) {return t1 > t2;};
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, decltype(compare)> pq(compare);

    for (int i = 0; i < a.size(); i++) {
        pq.push(make_tuple(a[i][0], i, 0));
    }

    vector<int> res;
    while(!pq.empty()) {
        auto v = pq.top();
        pq.pop();
        res.push_back(get<0>(v));
        int i = get<1>(v), j = get<2>(v) + 1;
        if (j >= a[i].size()) continue;
        pq.push(make_tuple(a[i][j], i, j));
    }

    return res;
}

void testKWayMerge() {
    // 1, 3, 4, 5, 6, 7, 9, 11
    vector<vector<int>> a = {
        {1, 4, 7},
        {5, 9},
        {3, 6, 7, 11}
    };

    auto res = kWayMerge2(a);

    for (auto x : res) cout << x << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    testKWayMerge();
    return 0;
}
