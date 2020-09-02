#include <iostream>
#include <vector>
using namespace std;

string toString(vector<int> v) {
    string ans = "[";
    for (int i: v) {
        ans += i + '0';
        ans += ", ";
    }
    ans = ans.substr(0, ans.length() - 2) + "]";
    return ans;
}

string toString(vector<vector<int>> v) {
    string ans = "[";
    for (vector<int> i: v) {
        ans += toString(i);
        ans += ", ";
    }
    ans = ans.substr(0, ans.length() - 2) + "]";
    return ans;
}

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> path;
        combinationSum(1, n, k, path);
        return result;
    }
private:
    void combinationSum(int index, int target, int k, vector<int> &path) {
        if (target == 0 && path.size() == k) {
            result.push_back(path);
            cout << "found: " << toString(path) << endl;
            cout << "found: " << toString(result) << endl;
            return;
        }
        if (target < 0 || index > 9 || path.size() == k) {
            cout << "return" << endl;
            return;
        }

        cout << "before(push): " << toString(path) << endl;
        path.push_back(index);
        cout << "after(push): " << toString(path) << endl;
        combinationSum(index+1, target-index, k, path);
        cout << "before(pop): " << toString(path) << endl;
        path.pop_back();
        cout << "after(pop): " << toString(path) << endl;
        combinationSum(index+1, target, k, path);
        cout << "finish second: " << toString(path) << endl;
    }
    vector<vector<int>>result;
};

void testCombSum3() {
    Solution sol;
    auto res = sol.combinationSum3(3, 7);
    for (auto row : res) {
        for (auto c : row) cout << c << " ";
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    testCombSum3();
    return 0;
}
