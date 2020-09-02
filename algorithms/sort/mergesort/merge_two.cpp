#include <iostream>
#include <vector>
using namespace std;

vector<int> mergeTwo(vector<int>& a, vector<int>& b) {
    int na = a.size(), nb = b.size();
    int i = 0, j = 0, k = 0;
    vector<int> res(na + nb, 0);
    while(i < na && j < nb) {
        if (a[i] < b[j]) res[k++] = a[i++];
        else res[k++] = b[j++];
    }

    while(i < na) res[k++] = a[i++];
    while(j < nb) res[k++] = b[j++];

    return res;
}

vector<int> mergeTwo1(vector<int>& a, vector<int>& b) {
    int na = a.size(), nb = b.size();
    int i = 0, j = 0, k = 0;
    vector<int> res(na + nb, 0);
    while(i < na || j < nb) {
        if (i < na && (j >= nb || a[i] < b[j])) res[k++] = a[i++];
        else res[k++] = b[j++];
    }

    // while(i < na) res[k++] = a[i++];
    // while(j < nb) res[k++] = b[j++];

    return res;
}

vector<int> mergeTwo2(vector<int>& a, vector<int>& b) {
    if (a.empty()) return b;
    if (b.empty()) return a;
    vector<int> res(a.size() + b.size());
    for (int i = 0, j = 0, k = 0; k < a.size() + b.size(); k++) {
        if (i == a.size()) res[k] = b[j++];
        else if (j == b.size()) res[k] = a[i++];
        else if (a[i] > b[j]) res[k] = b[j++];
        else res[k] = a[i++];
    }
    return res;
}

vector<int> mergeTwo3(vector<int>& a, vector<int>& b) {
    vector<int> res (a.size() + b.size());
    int i = 0, j = 0, k = 0;
    while (i < a.size() || j < b.size()) {
        if (j == b.size() || (i < a.size() && a[i] < b[j])) {
            res[k++] = a[i++];
        } else res[k++] = b[j++];
    }

    return res;
}

vector<int> mergeK(vector<vector<int>>& a) {
    vector<int> res;
    while (a.size() > 1) {
        vector<vector<int>> tmp;
        for (int i = 0; i < a.size() - 1; i += 2) {
            auto merged = mergeTwo(a[i], a[i+1]);
            tmp.push_back(merged);
        }
        if (a.size() & 1)
            tmp.push_back(a[a.size() - 1]);
        a = tmp;
    }
    return a[0];
}

void testMergeTwo() {
    vector<int> a {0, 1, 4};
    vector<int> b {2, 3, 5, 6, 9};

    auto res = mergeTwo2(a, b);
    for(auto v : res) cout << v << " "; cout << endl;

    res = mergeTwo3(a, b);
    for(auto v : res) cout << v << " "; cout << endl;
}

void testMergeK() {
    vector<vector<int>> a = {
        {1, 3, 7},
        {5, 8},
        {2, 4, 6, 9}
    };
    auto res = mergeK(a);

    for (auto v : res) cout << v << " "; cout << endl;
}

int main(int argc, char *argv[]) {
    testMergeTwo();
    // testMergeK();
    return 0;
}
