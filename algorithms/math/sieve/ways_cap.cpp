#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int countWays(vector<vector<int>>& persons) {
    // reverse index
    unordered_map<int, vector<int>> cap2person;
    // int m = 0;
    for (int i = 0; i < persons.size(); i++) {
        // m = max(m, (int)persons[i].size());
        for (int c : persons[i]) {
            cap2person[c].push_back(i);
        }
    }

    for (auto &[key, ps] : cap2person) {
        cout << key << ": ";
        for (auto p : ps) cout << p << " ";
        cout << endl;
    }
    cout << endl;

    int n = persons.size(), m = cap2person.size();
    vector<vector<int>> dp(1 << n, vector<int>(m + 1, 0));

    for (int mask = (1 << n) - 1; mask >= 0; mask--) {
        for (int i = 1; i <= cap2person.size(); i++) { // test each person to ware cap i
            if (mask == (1 << n) - 1) {
                dp[mask][i] = 1;
                continue;
            }
            auto cap = *std::next(cap2person.begin(), i - 1);
            for (int j = 0; j < cap.second.size(); j++) {
                if (mask & (1 << cap.second[j])) continue;
                else {
                    cout << mask << " | " << (1 << cap.second[j]) << endl;
                    dp[mask][i] += dp[mask | (1 << cap.second[j])][i-1] % 1000000007;
                    printf("dp[%d][%d] = %d\n", mask, i, dp[mask][i]);
                }
            }
        }
    }

    return dp[(1 << n) - 1][m];
}

void testCountWays() {
    vector<vector<int>> persons = {
        {5, 100, 1},
        {2},
        {5, 100}
    };
    cout << countWays(persons) << endl;
}

int main(int argc, char *argv[]) {
    testCountWays();
    return 0;
}
