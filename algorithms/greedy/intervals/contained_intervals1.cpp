#include <iostream>
#include <vector>
using namespace std;

struct Interval {
    int l, r;
};
bool operator==(const Interval& lhs, const Interval& rhs) {
    return (lhs.l == rhs.l) && (lhs.r == rhs.r);
}
bool myfunction (Interval i,Interval j) {
    if(i.l != j.l)  return (i.l < j.l);
    return (i.r > j.r);
}

int containedIntervals(vector<Interval>& intervals) {
    if(intervals.empty())   return 0;
    sort(intervals.begin(), intervals.end(), myfunction);
    int currentMaxR = 0;
    int res = intervals.size() > 1 && intervals[0] == intervals[1] ? 0 : -1;
    currentMaxR = intervals[0].r;
    int i = 0;
    for(;i < intervals.size()-1; ++i) {
        if(intervals[i] == intervals[i+1] || intervals[i].r <= currentMaxR)  ++res;
        currentMaxR = max(currentMaxR, intervals[i].r);
    }

    cout << i << ", " << intervals[i].r << ", "<< currentMaxR << endl;
    if(intervals[i].r <= currentMaxR)   ++res;
    return res;
}

void testContained() {
    vector<Interval> intervals = {
        {1, 3}, {1, 2}, {3, 4}, {3, 4}, {2, 3}
    };

    cout << containedIntervals(intervals) << endl;
}

int main(int argc, char *argv[]) {
    testContained();
    return 0;
}
