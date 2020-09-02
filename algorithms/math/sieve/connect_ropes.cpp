#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int getMinimumCost(vector<int>& ropes){
    priority_queue<int, vector<int>, greater<int>> minHeap;

    for(auto v : ropes) {
        minHeap.push(v);
    }

    int totalLength = 0;

    while(minHeap.size() > 1){
        int len1 = minHeap.top(); minHeap.pop();
        int len2 = minHeap.top(); minHeap.pop();

        cout << len1 << " " << len2 << endl;
        totalLength += (len1 + len2);

        minHeap.push(len1+len2);
    }

    return totalLength;
}

void testMinCost() {
    vector<int> ropes {5, 2, 3, 9, 4};
    cout << getMinimumCost(ropes) << endl;
}

int main(int argc, char *argv[]) {
    testMinCost();
    return 0;
}
