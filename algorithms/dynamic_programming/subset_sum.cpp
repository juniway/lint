#include <iostream>
#include <vector>
using namespace std;

// Return true if there exists a subarray of array[0..n] with given sum
bool subsetSum(int arr[], int n, int sum){
    if (sum == 0)
        return true;

    // base case: no items left or sum becomes negative
    if (n < 0 || sum < 0)
        return false;

    // Case 1. include current item in the subset (arr[n]) and recur
    // for remaining items (n - 1) with remaining sum (sum - arr[n])
    bool include = subsetSum(arr, n - 1, sum - arr[n]);

    // Case 2. exclude current item n from subset and recur for
    // remaining items (n - 1)
    bool exclude = subsetSum(arr, n - 1, sum);

    // return true if we can get subset by including or excluding the
    // current item
    return include || exclude;
}


// backtrack to find the solution
vector<vector<int>> res;
void find(vector<int>& A, int curSum, int index, int sum, vector<int>& sol) {
    if (curSum == sum) {
        vector<int> solu;
        for (int i = 0; i < sol.size(); i++) {
            if (sol[i] == 1)
                solu.push_back(A[i]);
        }
        res.push_back(solu);
    } else if (index == A.size()){
        return;
    } else {
        sol[index] = 1;
        curSum += A[index];
        find(A, curSum, index + 1, sum, sol); // select this item
        curSum -= A[index];
        sol[index] = 0;
        find(A, curSum, index + 1, sum, sol); // not select this item
    }
    return;
}

void testBT() {
    vector<int> A = {3, 2, 7, 1, 4};
    vector<int> sol(A.size());
    find(A, 0, 0, 6, sol);

    for (auto x : res) {
        for (auto y : x) cout << y << " ";
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    testBT();
    return 0;
}
