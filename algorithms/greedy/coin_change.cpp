#include <iostream>
#include <vector>
using namespace std;

vector<int> findMinCoins(int V, vector<int>& deno) {
    sort(begin(deno), end(deno));

    vector<int> res;
    for (auto it = deno.rbegin(); it != deno.rend(); it++) {
        while (V >= *it) {
            V -= *it;
            res.push_back(*it);
        }
    }

    return res;
}

void testFindMinCoins() {
    vector<pair<int, vector<int>>> denos = {
        {200, {1, 2, 5, 10, 20, 50, 100, 500, 1000}}, // expect: 100, 100
        {11, {9, 6, 5, 1}}, // expect: 6, 5
    };

    for (auto deno : denos) {
        auto res = findMinCoins(deno.first, deno.second);
        for (auto v : res) cout << v << " "; cout << endl;
    }
}

int main(int argc, char *argv[]) {
    testFindMinCoins();
    return 0;
}
