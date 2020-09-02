#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

int minNumbers(vector<int>& a, int sum) {
    queue<int> q;
    q.push(sum);
    unordered_set<int> visited;
    int n = 0;
    while(!q.empty()) {
        int s = q.size();
        while (s--) {
            int val = q.front();
            q.pop();
            if(val == 0) return n;
            if (visited.find(val) != visited.end() || val < 0)
                continue;
            visited.insert(val);
            for (int i = 0; i < a.size(); i++) {
                q.push(sum - a[i]);
            }
        }
        n++;
    }

    return -1;
}
