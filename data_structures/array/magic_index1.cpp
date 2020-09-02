#include <iostream>
#include <vector>
using namespace std;

int findMagicIndex(vector<int>& a) {
    int low = 0, high = a.size() - 1;
    while(low <= high) {
        int mid = (low + high) / 2;
        if (a[mid] >= mid)
            high = mid - 1;
        else low = mid + 1;
    }

    return a[low] == low ? low : -1;
}

void testFindMagic() {
    vector<int> a {-2, -1, 2, 4};
    cout << findMagicIndex(a) << endl;
    vector<int> b {1, 2};
    cout << findMagicIndex(b) << endl;
}

int main(int argc, char *argv[]) {
    testFindMagic();
    return 0;
}
