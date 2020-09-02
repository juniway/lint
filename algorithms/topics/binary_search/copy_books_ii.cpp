#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool isValid(vector<int>& times, int n, int x) {
    int cnt = 0;
    for (auto t : times) {
        cnt += x / t;
    }
    return cnt >= n;
}

int copyBooksII(vector<int>& times, int n) {
    int low = *min_element(times.begin(), times.end());
    int high = low * n;
    cout << low << "-" << high << endl;

    int minMinutes = 0;
    while(low <= high) {
        int mid = (low + high) / 2;
        cout << low << "-" << high << "-" << mid << endl;
        if (isValid(times, n, mid)) {
            high = mid - 1;
            minMinutes = mid;
        } else {
            low = mid + 1;
        }
    }

    return minMinutes;
}

void testCopyBooksII() {
    vector<int> times {3, 2, 4};
    cout << copyBooksII(times, 4) << endl;
}

int main(int argc, char *argv[]) {
    testCopyBooksII();
    return 0;
}
