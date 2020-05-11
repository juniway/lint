#include <iostream>
#include <cstdlib>
#include <limits>

int bruteforce(int a[], int n) {
    for (int i = 0; i <= n; i++) printf("%d ", a[i]);
    std::cout << "\n";
    int min = INT_MAX;
    for (int i = 0; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int d = std::abs(a[i] - a[j]);
            if (d < min)
                min = std::min(a[i], a[j]);
        }
    }

    return min;
}

int divide(int a[], int low, int high) {
    if (high - low <= 3) return bruteforce(a + low, high - low);
    int mid = low + (high - low)/2;
    int left_closest = divide(a, low, mid);
    int right_closest = divide(a, mid+1, high);
    int d = std::min(left_closest, right_closest);
    std::cout << "d: " << d << "\n";
    int mid_closest = std::min(std::abs(a[mid-1] - a[mid]), std::abs(a[mid+1] - a[mid]));

    return std::min(d, mid_closest);
}

int closestDistance(int a[], int n) {
    return divide(a, 0, n - 1);
}

void TestClosestDistance() {
    int a[]{7, 3, 9, 6, 5, 11, 8, 4, 1, 10};
    std::cout << closestDistance(a, 10) << "\n";
}

int main(int argc, char *argv[]) {
    TestClosestDistance();
    return 0;
}
