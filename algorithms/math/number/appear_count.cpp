// Given array A, containing numbers ranging from 0 to n,
// some numbers are missing, and some numbers are duplicated.
// return the missed number and the count of duplications for each number
//

#include <iostream>
#include <vector>
using namespace std;

vector<int> findRepetitions(vector<int>& nums) {
    int n = nums.size();
    vector<int> res;

    for (int i = 0; i < n; i++)
        nums[nums[i] % n] += n;

    for(auto v: nums) cout << v << " "; cout << endl;
    for (int i = 0; i < n; i++)
        res.push_back(nums[i] / n);

    return res;
}

void testFindRepetitions() {
    vector<int> a {2, 3, 1, 3};

    auto res = findRepetitions(a);
    for (auto v : res) cout << v << " "; cout << endl;
}

int main(int argc, char *argv[]) {
    testFindRepetitions();
    return 0;
}

