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
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> ans;
        vector<int> sol;
        combSum(candidates, 0, target, sol, ans);
        return ans;
    }

    void combSum(vector<int>& candidates, int start, int target,
                        vector<int>& sol, vector<vector<int>>& ans) {

        cout << "target: " << target << "start: " << start << endl;
        if (target < 0 || start >= candidates.size()) return;
        else if (target == 0) {
            ans.push_back(sol);
            return;
        }

        cout << "before(push): "<< candidates[start] << "|=| "<<  toString(sol) << endl;
        sol.push_back(candidates[start]);
        cout << "after(push): "<< candidates[start] << "|=| "<<  toString(sol) << endl;
        combSum(candidates, start + 1, target - candidates[start], sol, ans);
        cout << "before(pop): "<< candidates[start] << "|=| "<<  toString(sol) << endl;
        sol.pop_back();
        cout << "after(pop): "<< candidates[start] << "|=| "<<  toString(sol) << endl;
        combSum(candidates, start + 1, target, sol, ans);
        cout << "finished\n";
    }
};

void testCombSum() {
    vector<int> cand = {
        2,3,6,7
    };

    Solution sol;
    auto res = sol.combinationSum(cand, 7);
}

int main(int argc, char *argv[]) {
    testCombSum();
    return 0;
}
