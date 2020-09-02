#include <iostream>
#include <vector>
#include <map>
using namespace std;

int minMeetingRooms(vector<vector<int>>& intervals) {
    map<int, int> changes;
    for (auto i : intervals) {
        changes[i[0]] += 1;
        changes[i[1]] -= 1;
    }
    int rooms = 0, maxrooms = 0;
    for (auto change : changes)
        maxrooms = max(maxrooms, rooms += change.second);
    return maxrooms;
}

void testMeetRoomII() {
    vector<vector<int>> intervals {
        {1, 3}, {3, 5}, {4, 7}
    };

    cout << minMeetingRooms(intervals) << endl;
}

int main(int argc, char *argv[]) {
    testMeetRoomII();
    return 0;
}
