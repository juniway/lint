#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
    if (intervals.size() == 0) return {};
    sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
            return a[0] <= b[0];
            });

    vector<vector<int>> result;
    result.push_back(intervals[0]);
    for (int i = 1; i < intervals.size(); i++) {
        if(result.back()[1] < intervals[i].front()) {
            result.push_back(intervals[i]);
        } else {
            result.back()[1] = max(result.back()[1], intervals[i].back());
        }
    }

    return result;
}

void testMergeIntervals() {
    vector<vector<int>> intervals = {
        {1, 3}, {2, 6}, {8, 10}, {15, 18}
    };

    auto res = mergeIntervals(intervals);
    for (auto x : res) {
        for (auto y : x) cout << y << " ";
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    testMergeIntervals();
    return 0;
}
