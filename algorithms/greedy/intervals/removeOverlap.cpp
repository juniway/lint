#include <iostream>
#include <vector>
using namespace std;

// sort by start
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
        return a[0] < b[0];
    });

    int res = 0, minEnd = 0;
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] < intervals[minEnd][1]) {
            res++;
            if (intervals[i][1] < intervals[minEnd][1])
                minEnd = i;
        }
        else {
            minEnd = i;
        }
    }

    return res;
}

// sort by end
int eraseOverlapIntervals1(vector<vector<int>>& intervals) {
    sort(begin(intervals), end(intervals), [](vector<int>& a, vector<int>& b){
        return a[1] < b[1];
    });

    int res = 0, maxEnd = 0;
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] >= intervals[maxEnd][1])
            maxEnd = i;
        else
            res++;
    }

    return res;
}

void testEraseOverlap() {
    vector<vector<int>> intervals = {
        {1, 3}, {2, 4}, {5, 7}, {3, 6}
    };

    cout << eraseOverlapIntervals(intervals) << endl;
    cout << eraseOverlapIntervals1(intervals) << endl;
}

int main(int argc, char *argv[]) {
    testEraseOverlap();
    return 0;
}
