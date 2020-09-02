#include <iostream>
#include <vector>
using namespace std;

// sort by end
vector<vector<int>> selectActivity(vector<vector<int>>& activities) {
    sort(begin(activities), end(activities), [](vector<int>& a, vector<int>& b) {
        return a[1] < b[1];
    });

    int end = 0;
    vector<vector<int>> res(1, activities[0]);
    for (int i = 1; i < activities.size(); i++) {
        if (activities[i][0] >= activities[end][1]) {
            res.push_back(activities[i]);
            end = i;
        }
    }
    return res;
}

// sort by start
vector<vector<int>> selectActivity1(vector<vector<int>>& activities) {
    sort(begin(activities), end(activities), [](vector<int>& a, vector<int>& b) {
        return a[0] < b[0];
    });

    int end = 0;
    vector<vector<int>> res(1, activities[0]);
    for (int i = 1; i < activities.size(); i++) {
        if (activities[i][0] >= activities[end][1]) { // not overlap
            res.push_back(activities[i]);
            end = i;
        }
        else { // overlap
            if (activities[i][1] < activities[end][1]) {
                res.back()[0] = activities[i][0];
                res.back()[1] = activities[i][1];
                end = i;
            }
        }
    }
    return res;
}

void testSelectActivity() {
    vector<vector<int>> activities = {
        {1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 8}, {5, 9},
        {6, 10}, {8, 11}, {8, 12}, {2, 13}, {12, 14}, {9, 16}, {11, 12}, {11, 17}, {16, 22}, {17, 20
    },{21, 26}};

    auto res = selectActivity(activities);
    for (auto p : res) cout << "{" << p[0] << ", " << p[1] << "}, ";
    cout << endl;
    auto res1 = selectActivity1(activities);
    for (auto p : res1) cout << "{" << p[0] << ", " << p[1] << "}, ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    testSelectActivity();
    return 0;
}
