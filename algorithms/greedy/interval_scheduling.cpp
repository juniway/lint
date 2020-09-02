// Interval Scheduling problem
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

vector<pair<int, int>> intervalScheduling(vector<int>& stimes, vector<int>& ftimes, int n) {
    vector<pair<int, int>> jobs;
    for (int i = 0; i < stimes.size(); ++i) {
        jobs.push_back(make_pair(stimes[i], ftimes[i]));
    }

    sort(jobs.begin(), jobs.end(), [](pair<int, int> p1, pair<int, int> p2) {
        return p1.second < p2.second;
            });

    vector<pair<int, int>> result;
    int prev_finish_time = 0;

    for (int i = 0; i < jobs.size(); i++) {
        if(jobs[i].first >= prev_finish_time) {
            result.push_back(jobs[i]);
            prev_finish_time = jobs[i].second;
        }
    }

    return result;
}

void testIntervalScheduling() {
    vector<int> stimes {1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
    vector<int> ftimes {4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16};
    auto res = intervalScheduling(stimes, ftimes, 11);

    for (auto x : res) {
        cout << "(" << x.first << ", " << x.second << ")" << endl;
    }
    cout << endl;
}

int main(int argc, char *argv[]) {
    testIntervalScheduling();
    return 0;
}

