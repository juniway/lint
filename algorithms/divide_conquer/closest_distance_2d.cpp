#include <iostream>
#include <cstdlib>
#include <cmath>
// #include <cfloat>
#include <limits>
#include <vector>

struct Point {
    int x, y;
};


int compareX(const void *a, const void *b) {
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->x - p2->x);
}

int compareY(const void *a, const void *b) {
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->y - p2->y);
}

float dist(Point p1, Point p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

float bruteForce(Point p[], int n) {
    // float min = FLT_MAX; // #include <cfloat>
    float min = std::numeric_limits<float>::min();
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (dist(p[i], p[j]) < min)
                min = dist(p[i], p[j]);
        }
    }
    return min;
}

float min(float x, float y) {
    return (x < y) ? x : y;
}

float stripClosest(Point strip[], int size, float d) {
    float min = d;
    std::qsort(strip, size, sizeof(Point), compareY);
    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            min = dist(strip[i], strip[j]);
    return min;
}

float closestUtil(Point p[], int n) {
    if (n <= 3)
        return bruteForce(p, n);
    int mid = n/2;
    Point midPoint = p[mid];
    float dl = closestUtil(p, mid);
    float dr = closestUtil(p + mid, n - mid);
    float d = min(dl, dr);

    // Point strip[n];
    std::vector<Point> strip(n);
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(p[i].x - midPoint.x) < d)
            strip[j] = p[i], j++;
    return min(d, stripClosest(&strip[0], j, d));
}

float closest(Point p[], int n) {
    qsort(p, n, sizeof(Point), compareX);
    return closestUtil(p, n);
}

int main() {
    Point P[] {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    int n = sizeof(P) / sizeof(P[0]);
    std::cout << "The closest distance is: " << closest(P, n) << "\n";
    return 0;
}
