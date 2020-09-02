#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

int minCoins(vector<int>& arr, int N) {
    int n = arr.size();
    queue<int> q;
    q.push(N);
    // vector<bool> visited;
    unordered_set<int> visited;

    int d = 0;
    while(!q.empty()) {
        int s = q.size();
        while (s--) {
            int c = q.front();
            if (c == 0) return d;
            q.pop();
            if(visited.find(c) != visited.end() or c < 0) {
                continue;
            }

            visited.insert(c);
            for(int i = 0; i < n; i++) {
                q.push(c - arr[i]);
            }
        }
        d++;
    }

    return -1;
}

void testMinCoins() {
    vector<int> arr{3, 3, 4};
    cout << minCoins(arr, 12) << endl;
}

int main(int argc, char *argv[]) {
    testMinCoins();
    return 0;
}
