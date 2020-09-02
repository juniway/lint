#include <iostream>
#include <queue>
using namespace std;

class MedianFinder {
    priority_queue<int> small;
    priority_queue<int, vector<int>, std::greater<int>> large;
public:
    void addNum(int num) {
        small.push(num);
        large.push(small.top());
        small.pop();
        if (small.size() < large.size()) {
            small.push(large.top());
            large.pop();
        }
    }

    double findMedian() {
        return small.size() > large.size() ?
            (double)small.top() :
            (double) small.top() / 2 + (double) large.top() / 2;
    }
};

void testMedianFinder() {
    MedianFinder mf;
    mf.addNum(1);
    cout << mf.findMedian() << endl;
    mf.addNum(2);
    cout << mf.findMedian() << endl;
    mf.addNum(3);
    cout << mf.findMedian() << endl;
}

int main(int argc, char *argv[]) {
    testMedianFinder();
    return 0;
}
