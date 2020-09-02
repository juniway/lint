#include <iostream>
#include <vector>
using namespace std;

class SummaryRanges {
public:
    SummaryRanges() {}

    int binarySearch(int left, int right, int val) {
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (intervals[mid][0] <= val)
                left = mid;
            else right = mid - 1;
        }

        return right;
    }

    void addNum(int val) {
        vector<int> newInterval{val, val};
        int i = 0, overlap = 0, n = intervals.size();
        if (intervals.empty()) {
            intervals.push_back({val, val});
            return;
        }

        // find the greatest value that is smaller than val
        int index = binarySearch(0, intervals.size(), val);
        if (index > 0) index--; // if found, then we start from the last element within upper_bound

        for (i = index; i < n; i++) {
            if (newInterval[1] + 1 < intervals[i][0]) break; // non-overlap
            if (newInterval[0] <= intervals[i][1] + 1) {
                newInterval[0] = min(newInterval[0], intervals[i][0]);
                newInterval[1] = max(newInterval[1], intervals[i][1]);
                ++overlap;
            }
        }
        if (overlap > 0) {
            intervals.erase(intervals.begin() + i - overlap, intervals.begin() + i);
        }
        intervals.insert(intervals.begin() + i - overlap, newInterval);
    }
    vector<vector<int>> getIntervals() {
        return intervals;
    }
private:
    vector<vector<int>> intervals;
};

void printVector(const vector<vector<int>>& intervals) {
    for(auto x : intervals) {
        cout << x[0] << ", " << x[1] << endl;
    }
}

void testDisjointIntervals() {
    SummaryRanges ob;
    ob.addNum(1);
    printVector(ob.getIntervals());
    ob.addNum(3);
    printVector(ob.getIntervals());
    ob.addNum(8);
    printVector(ob.getIntervals());
    ob.addNum(2);
    printVector(ob.getIntervals());
    ob.addNum(7);
    printVector(ob.getIntervals());
}

int main(int argc, char *argv[]) {
    testDisjointIntervals();
    return 0;
}
