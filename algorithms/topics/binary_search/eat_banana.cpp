#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

bool isValid(vector<int>& piles, int H, int x) {
    int count = 0;
    for (auto p : piles) {
        count += p / x;
        if (p % x != 0)
            count++;
    }
    if (count <= H) return true;
    return false;
}

int minEatingSpeed(vector<int>& piles, int H) {
    // int low = accumulate(begin(piles), end(piles), 0) / 8;
    int low = 1;
    int high = *max_element(begin(piles), end(piles));

    int ans = high;
    while(low <= high) {
        // int mid = (low + high) / 2;
        int mid = low + (high - low) / 2;
        if (isValid(piles, H, mid)) {
            ans = min(ans, mid);
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ans;
}

void testEat() {
    vector<int> piles {3, 6, 7, 11};
    cout << minEatingSpeed(piles, 8) << endl;
}

int main(int argc, char *argv[]) {
    testEat();
    return 0;
}
