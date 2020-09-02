#include <iostream>
#include <vector>

using namespace std;

bool isValid(vector<int>& pages, int k, int x) {
    int count = 1, sum = 0;
    for (int p : pages) {
        if (p > x) return false;
        if (p + sum <= x) {
            sum += p;
        } else {
            count++;
            sum = p; // reset sum
        }
    }
    return count <= k;
}

int copyBooks(vector<int>& pages, int k) {
    int n = pages.size();
    if(n == 0 || k == 0) return 0;

    int maxPage = 0, sum = 0;
    for (int p : pages) {
        maxPage = max(maxPage, p);
        sum += p;
    }

    int left = maxPage, right = sum, ans = sum;
    while (left + 1 < right) {
        int mid = left + (right - left) / 2;
        if (isValid(pages, k, mid)) {
            ans = min(ans, mid);
            right = mid;
        } else {
            left = mid;
        }
    }

    cout << left << "-" << right << endl;
    if (isValid(pages, k, left)) return left;

    return right;
}

void testCopyBooks() {
    vector<int> pages {3, 2, 4};
    cout << copyBooks(pages, 2) << endl;
}

int main(int argc, char *argv[]) {
    testCopyBooks();
    return 0;
}
