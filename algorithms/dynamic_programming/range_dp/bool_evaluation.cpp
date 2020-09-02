#include <iostream>
#include <vector>
#include <string>

using namespace std;

int getOpResult(int val1, int val2, char op) {
    switch(op) {
        case '&':
            return val1 & val2;
        case '|':
            return val1 | val2;
        case '^':
            return val1 ^ val2;
    }
    return val1 & val2;
}

vector<vector<vector<int>>> dp;

// the number of result we can get from two operator
int rangeRec(string s, int start, int end, int result) {
    if (start == end)
        return s[start] - '0' == result ? 1 : 0;
    if (dp[start][end][result] != -1)
        return dp[start][end][result];

    int cnt = 0;
    for (int k = start; k < end; k += 2) {
        char op = s[k + 1];
        for (int i = 0; i <= 1; i++) {
            for (int j = 0; j <= 1; j++) {
                if (getOpResult(i, j, op) == result) {
                    cnt += rangeRec(s, start, k, i) * rangeRec(s, k + 2, end, j);
                }
            }
        }
    }

    dp[start][end][result] = cnt;
    return cnt;
}

int countEval(string s, int result) {
    dp = vector<vector<vector<int>>>(s.length(), vector<vector<int>>(s.length(), vector<int>(2, -1)));
    return rangeRec(s, 0, s.length() - 1, 0);
}

void testCountEval() {
    cout << countEval("1^0|0|1", 0) << endl;
}

int main(int argc, char *argv[]) {
    testCountEval();
    return 0;
}
