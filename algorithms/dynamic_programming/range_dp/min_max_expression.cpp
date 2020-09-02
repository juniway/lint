#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> findMinMaxExpression(string s) {
    vector<int> nums;
    vector<char> ops;

    string tmp = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '+' || s[i] == '*' || s[i] == '-') {
            ops.push_back(s[i]);
            nums.push_back(atoi(tmp.c_str()));
            tmp = "";
        } else {
            tmp += s[i];
        }
    }
    nums.push_back(atoi(tmp.c_str()));

    int n = nums.size();
    vector<vector<int>> minValues(n, vector<int>(n, INT_MAX));
    vector<vector<int>> maxValues(n, vector<int>(n, INT_MIN));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                minValues[i][j] = maxValues[i][j] = nums[i];
        }
    }

    for (int L = 2; L <= n; L++) {
        for (int i = 0; i < n - L + 1; i++) {
            int j = i + L - 1;
            for (int k = i; k < j; k++) {
                int minTmp = 0, maxTmp = 0;
                if (ops[k] == '+') {
                    minTmp = minValues[i][k] + minValues[k+1][j];
                    maxTmp = maxValues[i][k] + maxValues[k+1][j];
                } else if (ops[k] == '-') {
                    minTmp = minValues[i][k] - minValues[k+1][j];
                    maxTmp = maxValues[i][k] - maxValues[k+1][j];
                } else if (ops[k] == '*') {
                    minTmp = minValues[i][k] * minValues[k+1][j];
                    maxTmp = maxValues[i][k] * maxValues[k+1][j];
                }

                if (minValues[i][j] > minTmp)
                    minValues[i][j] = minTmp;
                if (maxValues[i][j] < maxTmp)
                    maxValues[i][j] = maxTmp;
            }
        }
    }

    return {minValues[0][n - 1], maxValues[0][n-1]};
}

void testMinMaxExpression(string s) {
    auto res = findMinMaxExpression(s);
    cout << "min: " << res[0] << ", max: " << res[1] << endl;
}

int main(int argc, char *argv[]) {
    testMinMaxExpression("1 + 2 * 3 + 4 * 5");
    testMinMaxExpression("10 - 2 * 5");
    testMinMaxExpression("5 - 8 + 7 * 4 - 8 + 9");
    testMinMaxExpression("5 - 8 + 7");
    testMinMaxExpression("4 - 8 + 9");
    return 0;
}
