#include <iostream>
#include <vector>

using namespace std;

int maxProfix(vector<int>& prices) {
    int begin = 0, end = 1, res = 0, localres = 0;
    while(end < prices.size()) {
        if (prices[end] >= prices[begin]) {
            localres = prices[end++] - prices[begin];
            res = max(res, localres);
        } else {
            begin++;
        }
    }

    return res;
}


