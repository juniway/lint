#include <iostream>
#include <vector>

using namespace std;

int maxProfix(vector<int>& prices) {
    if (prices.size() == 0) return 0;

    int maxProfix = 0;
    int lowest = INT_MAX;
    for (int v : prices) {
        lowest = min(v, lowest);
        maxProfix = max(maxProfix, v - lowest);
    }

    return maxProfix;
}

int maxProfit1(vector<int>& prices) {
    if (prices.size() == 0) return 0;
    int begin = 0, end = 1, res = 0, localres = 0;
    while (end != prices.size()) {
        if (prices[end] >= prices[begin]) {
            localres = prices[end++] - prices[begin];
            res = max(res, localres);
        } else {
            begin++;
        }
    }

    return res;
}
