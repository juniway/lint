#include <iostream>
#include <vector>

using namespace std;

vector<int> ReserviorSampling(vector<int>& results, vector<int>& nums, int k) {
    int N = nums.size();
    for (int i = 0; i < k; i++)
        results[i] = nums[i];

    for(int i = k; i < N; i++) {
        int x = rand() % i;
        if (x < k)
            results[x] = nums[i];
    }

    return results;
}
