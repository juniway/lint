#include <iostream>
#include <vector>
using namespace std;

struct Interval {
    int l, r;
};

bool operator==(const Interval& lhs, const Interval& rhs) {
    return lhs.l == rhs.l && lhs.r == rhs.r;
}

int containedIntervals(vector<Interval>& intervals) {
    if (intervals.empty()) return 0;

    sort(intervals.begin(), intervals.end(), [](Interval& a, Interval& b){
        if (a.l == b.l) return a.r > b.r;
        return a.l < b.l;
    });

    int res = 0;
    int currentEnd = intervals[0].r;
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i].l <= currentEnd && intervals[i].r <= currentEnd)
            res++;
        if (intervals[i] == intervals[i - 1]) res++;
        currentEnd = max(currentEnd, intervals[i].r);
    }
    return res;
}

int main() {
    int N;
    cin >> N;
    vector<Interval> intervals;
    for (int i = 0; i < N; ++i) {
        Interval interval;
        cin >> interval.l >> interval.r;
        intervals.push_back(interval);
    }

    cout << containedIntervals(intervals) << "\n";
    return 0;
}
