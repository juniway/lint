// jump2.cpp
// DP

// A[i] means the minimum steps from pos i to pos n-1. 
// i + A[i]  means the max pos i can reach
// The key idea is if A[i] > A[i - 1], pos i will never be the intermediate pos in the final path, 
// so just make pos i 'adjacent' to pos i-1.

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int jump(vector<int> A) {
    	int n = A.size();
        A[n - 1] = 0;
        for (int i = n - 2; i >= 0; i--) {
            int m = min(i + A[i], n - 1);
            A[i] = (m == i ? n : A[m] + 1);
            for(int j = i + 1; A[j] > A[i]; j++) 
            	A[j] = A[i];
        }
        return A[0] >= n ? -1 : A[0];
    }
};

int main(){
	vector<int> a = {3, 2, 1, 0, 4};
	Solution s;
	cout << "jumps:"<< s.jump(a) << endl;
}