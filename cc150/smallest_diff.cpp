#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int smallestDifference(vector<int>& a, vector<int>& b) {
    sort(a.begin(), a.end());
    double ans = 1e9;
    for (int k = 0; k < b.size(); k++) {
        int i = 0, j = a.size() - 1;
        while (i < j) {
            int mid = (i + j + 1) / 2;
            if (a[mid] <= b[k])
                i = mid;
            else j = mid - 1;
        }
        ans = min(ans, (double)abs((double)a[i] - (double)b[k]));
        if (i != a.size() - 1)
            ans = min(ans, (double)abs((double)a[i + 1] - (double)b[k]));
    }
    return ans;
}

void test() {
    vector<int> a {1, 3, 15, 11, 2}, b{23, 127, 235, 19, 8};
    cout << smallestDifference(a, b) << endl;
}

int main(int argc, char *argv[]) {
    test();
    return 0;
}
