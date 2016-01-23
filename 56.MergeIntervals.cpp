[LeetCode 56] Merge intervals
Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3], [2,6], [8,10], [15,18]
return [1,6], [8,10], [15,18].

class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), 
             [](const Interval &a, const Interval &b){return a.start < b.start;});
        vector<Interval> result;
        if(intervals.size() == 0) return result;
        result.push_back(intervals[0]);
        for(int i = 1; i < (int)intervals.size(); ++i){
            if(result.back().end < intervals[i].start){
                result.push_back(intervals[i]);
            }
            else // overlap
                result.back().end = max(result.back().end, intervals[i].end);
        }
        return result;
    }
};
