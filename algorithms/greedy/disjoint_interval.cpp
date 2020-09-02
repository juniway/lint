#include <iostream>
#include <vector>
#include <set>

using namespace std;

class SummaryRanges {
public:
    void addNum(int val) {
        nums.insert(val);
    }

    vector<vector<int>> getIntervals() {
        vector<vector<int>> result;
        set<int>::iterator it = nums.begin();
        while(it != nums.end()) {
            int val = *it++;
            if (result.empty() || result.back()[1] + 1 < val) {
                result.push_back({val, val});
            } else {
                result.back()[1]++;
            }
        }
        return result;
    }
private:
    set<int> nums;
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
