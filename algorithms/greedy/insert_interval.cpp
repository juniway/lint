#include <iostream>
#include <vector>
using namespace std;

int binarySearch(vector<vector<int>>& intervals, int left, int right, int val) {
    while (left + 1 < right) {
        int mid = left + (right - left) / 2;
        if (intervals[mid][0] <= val)
            left = mid;
        else right = mid - 1;
    }
    return right;
}

vector<vector<int>> insert0(vector<vector<int>>& intervals, vector<int>& newInterval) {
    if (intervals.empty()) return {newInterval};
    int index = binarySearch(intervals, 0, intervals.size(), newInterval[0]);
    if (index > 0) index--;

    int i = 0, overlap = 0;
    for (i = index; i < intervals.size(); i++) {
        if (newInterval[1] < intervals[i][0]) break;
        if (newInterval[0] <= intervals[i][1]) {
            newInterval[0] = min(intervals[i][0], newInterval[0]);
            newInterval[1] = max(intervals[i][1], newInterval[1]);
            overlap++;
        }
    }

    if (overlap > 0) {
        intervals.erase(intervals.begin() + i - overlap, intervals.begin() + i);
    }
    intervals.insert(intervals.begin() + i - overlap, newInterval);
    return intervals;
}

vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    if (intervals.empty()) return {newInterval};
    int i = 0;

    vector<vector<int>> result;
    while (i < intervals.size() && newInterval[0] > intervals[i][1])
        result.push_back(intervals[i++]);
    while(i < intervals.size() && newInterval[1] >= intervals[i][0]) {
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }
    result.push_back(newInterval);

    while(i < intervals.size()) result.push_back(intervals[i++]);
    return result;
}

void testInsertInterval() {
    vector<vector<int>> intervals = {
        {1, 3}, {6, 9}
    };
    vector<int> interval {2, 5};
    auto res = insert0(intervals, interval);

    for (auto x : res) {
        cout << x[0] << ", " << x[1] << endl;
    }
}

int main(int argc, char *argv[]) {
    testInsertInterval();
    return 0;
}
