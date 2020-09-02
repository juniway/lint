#include <iostream>
#include <vector>
using namespace std;

vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2,
        int duration) {
    sort(slots1.begin(), slots1.end());
    sort(slots2.begin(), slots2.end());
    int i = 0, j = 0;
    int n1 = slots1.size(), n2 = slots2.size();
    while (i < n1 && j < n2) {
        int intersectStart = max(slots1[i][0], slots2[j][0]);
        int intersectEnd = min(slots1[i][1], slots2[j][1]);
        if (intersectStart + duration <= intersectEnd) {
            return {intersectStart, intersectStart + duration};
        } else if (slots1[i][1] < slots2[j][1]) {
            i++;
        } else {
            j++;
        }
    }
    return {};
}

void testMeetScheduler() {
    vector<vector<int>> slots1 = {
        {10, 50}, {60, 120}, {140, 210},
    };
    vector<vector<int>> slots2 = {
        {0, 15}, {60, 70}
    };
    int duration = 8;

    auto res = minAvailableDuration(slots1, slots2, duration);

    for (auto x : res) {
        cout << x << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[]) {
    testMeetScheduler();
    return 0;
}
