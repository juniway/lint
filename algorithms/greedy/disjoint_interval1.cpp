#include <iostream>
#include <vector>
#include <set>

using namespace std;

class SummaryRanges {
public:
    void addNum(int val) {
        if (intervals.empty()) {
            intervals.push_back({val, val});
            return;
        }
        int index = binarySearch(0, intervals.size(), val);
        if (index == -1) {
            if (val + 1 == intervals.back()[0])
                intervals.back()[0] = val;
            else intervals.insert(intervals.begin(), {val, val});
        } else {
            if (val - 1 == intervals[index][1]) {
                intervals[index][1] = val;
            } else if (index + 1 < intervals.size() && val + 1 == intervals[index + 1][0])
                intervals[index + 1][0] = val;
            else {
                intervals.insert(intervals.begin() + index + 1, {val, val});
            }

            // merge intervals
            if (index + 1 < intervals.size() && intervals[index][1] + 1 == intervals[index + 1][0]) {
                intervals[index][1] = intervals[index + 1][1];
                intervals.erase(intervals.begin() + index + 1);
            }
        }

        return;
    }

    vector<vector<int>> getIntervals() {
        return intervals;
    }
private:
    vector<vector<int>> intervals;
    int binarySearch(int begin, int end, int val) {
        while (begin + 1 < end) {
            int mid = begin + (end - begin) / 2;
            if(intervals[mid][0] <= val) begin = mid;
            else end = mid - 1;
        }
        if(intervals[end][0] <= val) return end;
        if(intervals[begin][0] <= val) return begin;
        return -1;
    }
};

void printVector(const vector<vector<int>>& intervals) {
    for(auto x : intervals) {
        cout << x[0] << ", " << x[1] << endl;
    }
    cout << "================" << endl;
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
