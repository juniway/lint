#include <iostream>
using namespace std;

int sum(int n) {
    return n * (n + 1) / 2;
}

int arrangeCoins(int n) {
    int low = 1, high = n;
    while(low < high) {
        int mid = low + (high - low) / 2;
        cout << "before => low: " << low << ", mid: " << mid << ", high: " << high << endl;
        if (sum(mid) <= n)
            low = mid;
        else high = mid - 1;
        cout << "after => low: " << low << ", mid: " << mid << ", high: " << high << endl;
    }

    if (sum(high) <= n) return high;
    return low;
    // if (sum(low) <= n) return low;
    // return -1;
}

void testArrangeCoins() {
    cout << arrangeCoins(0) << endl;
}

int main(int argc, char *argv[]) {
    testArrangeCoins();
    return 0;
}
